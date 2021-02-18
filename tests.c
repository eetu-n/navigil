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

START_TEST (single_button_blink_return){
    init();
    button_on(1);
    for(int i = 0; i < 25; i++) timer();
    button_off(1);
    for(int i = 0; i < 301; i++) timer();

    ck_assert(!is_led_blinking(1) && !is_led_on(1));
} END_TEST

START_TEST (single_button_blink_alternate){
    bool passed = true;
    init();
    button_on(1);
    for(int i = 0; i < 25; i++) timer();
    button_off(1);
    for(int i = 0; i < 301; i++){
        timer();
        if((i / 5) % 2){
            if(!is_led_on(1)) passed = false;
        } else {
            if(is_led_on(1)) passed = false;
        }
    }

    ck_assert(passed);
} END_TEST

START_TEST (multi_button_blink_alternate){
    bool passed = true;
    init();
    button_on(1);
    button_on(9);
    for(int i = 0; i < 25; i++) timer();
    button_off(1);
    button_off(9);
    for(int i = 0; i < 301; i++){
        timer();
        if((i / 5) % 2){
            if(!is_led_on(1)) passed = false;
            if(!is_led_on(9)) passed = false;
        } else {
            if(is_led_on(1)) passed = false;
            if(is_led_on(9)) passed = false;
        }
    }

    ck_assert(passed);
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
    tcase_add_test(tc_core, single_button_blink_return);
    tcase_add_test(tc_core, single_button_blink_alternate);
    tcase_add_test(tc_core, multi_button_blink_alternate);

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