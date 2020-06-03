int FLAGS_hidden_1 __attribute__((visibility("hidden"))) = 1;
int FLAGS_hidden_2 __attribute__((visibility("hidden"))) = 2;
int FLAGS_protected_1 __attribute__((visibility("protected"))) = 1;
int FLAGS_protected_2 __attribute__((visibility("protected"))) = 2;

__attribute__((visibility("default"))) int FLAGS_default_get()
{
    return FLAGS_hidden_1;
}

__attribute__((visibility("hidden"))) void FLAGS_hidden_set(int a)
{
    FLAGS_protected_1 = a;
}

__attribute__((visibility("protected"))) int FLAGS_protected_add()
{
    return FLAGS_hidden_2 + FLAGS_protected_2;
}
