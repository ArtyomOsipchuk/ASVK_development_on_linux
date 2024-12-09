#include "../lib/libguess.h"
#include <check.h>

#test dummy
    ck_assert_ptr_ne(to_roman, NULL);
    ck_assert_ptr_ne(to_arabic, NULL);
