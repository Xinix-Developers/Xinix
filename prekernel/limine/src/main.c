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

  char *argv[] = {"kernel", 0};
  char *envp[] = {0};
  auxv_t auxv[] = {
      {AT_IGNORE},
      {0},
  };

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
    auxv[0] = auxv_fb;
  }

  kmain(1, argv, envp, auxv);
}
