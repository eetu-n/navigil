#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "led_and_button_controller.h"
#include "external.h"
#include "light_wrapper.h"

START_TEST (single_button_no_action){
    init();
    button_on(1);
    timer();
    timer();
    timer();
    button_off(1);
    timer();

    ck_assert(!is_led_on(1));
} END_TEST

START_TEST (single_button_toggle){
    init();
    button_on(1);
    timer();
    timer();
    timer();
    timer();
    timer();
    button_off(1);
    timer();

    ck_assert(is_led_on(1));
} END_TEST

START_TEST (single_button_blink){
    init();
    button_on(1);
    for(int i = 0; i < 25; i++) timer();
    button_off(1);
    timer();

    ck_assert(is_led_blinking(1));
} END_TEST

Suite * main_suite(void){
    Suite *s;
    TCase *tc_core;

    s = suite_create("General Tests");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, single_button_no_action);
    tcase_add_test(tc_core, single_button_toggle);
    tcase_add_test(tc_core, single_button_blink);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    int number_failed;
    SRunner *sr;

    sr = srunner_create(main_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}