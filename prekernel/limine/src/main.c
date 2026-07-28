#include "random.h"
#include <stdint.h>

#include <auxv.h>
#include <framebuffer.h>

#include <limine.h>

/// LIMINE REQUESTS ///

[[gnu::used, gnu::section(".limine_requests")]]
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

[[gnu::used, gnu::section(".limine_requests")]]
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
};

[[gnu::used, gnu::section(".limine_requests_start")]]
static volatile uint64_t limine_requests_start_marker[] =
    LIMINE_REQUESTS_START_MARKER;

[[gnu::used, gnu::section(".limine_requests_end")]]
static volatile uint64_t limine_requests_end_marker[] =
    LIMINE_REQUESTS_END_MARKER;

/// FUNCTION PROTOTYPES ///

[[noreturn]]
extern void kmain(int argc, char *argv[], char *envp[], auxv_t auxv[]);

extern void init_cpu_feature_array(void);

/// IMPLEMENTATION ///

[[noreturn]]
static void hcf(void) {
  for (;;) {
    __asm__("hlt");
  }
}

[[noreturn]]
void pkmain(void) {
  if (!LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision)) {
    hcf();
  }

  init_cpu_feature_array();

  char *argv[] = {"kernel", 0};
  char *envp[] = {0};
  auxv_t auxv[16] = {
      {0},
  };

  auxv_t *auxtarg = auxv;

  char cpu_name[] = ARCH;

  *auxtarg++ = (auxv_t){.a_type = AT_PAGESZ, .a_un.a_val = 4096};
  *auxtarg++ = (auxv_t){.a_type = AT_PLATFORM, .a_un.a_ptr = cpu_name};

  if (framebuffer_request.response != nullptr &&
      framebuffer_request.response->framebuffer_count >= 1) {
    struct limine_framebuffer *l_fb =
        framebuffer_request.response->framebuffers[0];
    framebuffer fb = {
        .address = l_fb->address,
        .mode_count = l_fb->mode_count,
        .modes = (video_mode **)l_fb->modes,
    };
    auxv_t auxv_fb = {AT_KXINIX_FRAMEBUFFER, {.a_ptr = (void *)&fb}};
    *auxtarg++ = auxv_fb;
  }

  uint8_t random[16];
  if (rand_slow_get_entropy(random) == 0)
    *auxtarg++ = (auxv_t){.a_type = AT_RANDOM, .a_un.a_ptr = random};

  kmain(1, argv, envp, auxv);
}
