typedef struct {
  int a_type;
  union {
    long a_val;
    void *a_ptr;
    void (*a_fnc)();
  } a_un;
} auxv_t;

// a_type values
#define AT_NULL 0               // end of list
#define AT_IGNORE 1             // no-op entry
#define AT_KZINIX_FRAMEBUFFER 2 // framebuffer structure
