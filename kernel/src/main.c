#include <auxv.h>
#include <framebuffer.h>

#include <flanterm.h>
#include <flanterm_backends/fb.h>

[[noreturn]]
static void hcf(void) {
  for (;;) {
    __asm__("hlt");
  }
}

[[noreturn]]
extern void kmain(int argc, char *argv[], char *envp[], auxv_t auxv[]) {
  framebuffer *fb;

  for (auxv_t *auxv_ent = auxv; auxv_ent->a_type != AT_NULL; auxv_ent++) {
    switch (auxv_ent->a_type) {
    case AT_KXINIX_FRAMEBUFFER:
      fb = (framebuffer *)auxv_ent->a_un.a_ptr;
      break;
    }
  }

  video_mode *fb_mode = fb->modes[0];
  // Pick the highest-resolution mode we can find that flanterm will understand
  // Note: this doesn't actually work right now because we don't change the framebuffer size, and that causes issues.
  // TODO: Figure out how to do resizing correctly
  // TODO 2: abstract the terminal into a driver
  for (int i = 0; i < fb->mode_count; i++) {
    video_mode *test_mode = fb->modes[i];
    if (test_mode->pitch >= test_mode->width * 4) {
      if ((fb_mode == NULL || test_mode->width * test_mode->height >=
                                  fb_mode->width * fb_mode->height) &&
          test_mode->width <= 1920 && test_mode->height <= 1200) {
        fb_mode = test_mode;
      }
    }
  }

  struct flanterm_context *ft_ctx = flanterm_fb_init(
      nullptr, nullptr, fb->address, fb_mode->width, fb_mode->height,
      fb_mode->pitch, fb_mode->red_mask_size, fb_mode->red_mask_shift,
      fb_mode->green_mask_size, fb_mode->green_mask_shift,
      fb_mode->blue_mask_size, fb_mode->blue_mask_shift, nullptr, nullptr,
      nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, 1, 0, 0, 0,
      0);

  const char msg[] = "Xinix Version 0.0.0\r\n(that's right, even less than 0.0.1)\r\n";
  flanterm_write(ft_ctx, msg, sizeof(msg));

  hcf();
}
