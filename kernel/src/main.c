#include "cpuid.h"
#include <auxv.h>
#include <framebuffer.h>
#include <memory.h>
#include <stdio.h>

#include <flanterm.h>
#include <flanterm_backends/fb.h>

[[noreturn]]
static void hcf(void) {
    for (;;) {
        __asm__("hlt");
    }
}

static union auxval_t __auxent[128 - 2];

union auxval_t getauxval(unsigned long a_type) {
    if (a_type < 2 || a_type > 128)
        return (union auxval_t){};
    else
        return __auxent[a_type - 2];
}

size_t stdout_handler(void *data, size_t len, const char *bytes) {
    struct flanterm_context *ft_ctx = data;
    flanterm_write(ft_ctx, bytes, len);
    return len;
}

void print_feature_flag(void *v_want_comma, enum x86_feature_flag flag) {
    bool *want_comma = (bool *)v_want_comma;
    const char *name = x86_get_feature_name(flag);
    if (*want_comma) {
        printf(", %s", name);
    } else {
        printf("%s", name);
    }
    *want_comma = true;
}

[[noreturn]]
extern void kmain(int argc, char *argv[], char *envp[], auxv_t auxv[]) {
    framebuffer *fb;

    for (auxv_t *auxv_ent = auxv; auxv_ent->a_type != AT_NULL; auxv_ent++) {
        if (auxv_ent->a_type != AT_IGNORE)
            __auxent[auxv_ent->a_type - 2] = auxv_ent->a_un;
    }

    fb = (framebuffer *)getauxval(AT_KXINIX_FRAMEBUFFER).a_ptr;

    video_mode *fb_mode = fb->modes[0];
    // Pick the highest-resolution mode we can find that flanterm will
    // understand Note: this doesn't actually work right now because we don't
    // change the framebuffer size, and that causes issues.
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

    const char msg[] =
        "Xinix Version 0.0.0\r\n(that's right, even less than 0.0.1)\r\n\r\n";
    flanterm_write(ft_ctx, msg, sizeof(msg));

    char *alloc_test = malloc(40);
    memcpy(alloc_test, "Did malloc work?\r\nOf course it did :D\r\n", 40);
    flanterm_write(ft_ctx, alloc_test, 40);

    stdout = calloc(1, sizeof(FILE));
    stdout->data = ft_ctx;
    stdout->write = stdout_handler;

    printf("Address of printf is %#.16X\r\n", printf);

    printf("Feature flags: ");
    bool want_comma = false;
    x86_enumerate_supported_features(print_feature_flag, &want_comma);
    printf("\r\n");

    hcf();
}
