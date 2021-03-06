/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <usb/usb_device.h>
#include <usb/class/usb_hid.h>

#include <zmk/keys.h>

#define COLLECTION_REPORT 0x03

#define ZMK_HID_KEYPAD_NKRO_SIZE 6

#define ZMK_HID_CONSUMER_NKRO_SIZE 6

static const u8_t zmk_hid_report_desc[] = {
    /* USAGE_PAGE (Generic Desktop) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP,
    /* USAGE (Keyboard) */
    HID_LI_USAGE,
    USAGE_GEN_DESKTOP_KEYBOARD,
    /* COLLECTION (Application) */
    HID_MI_COLLECTION,
    COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID,
    0x01,
    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* USAGE_MINIMUM (Keyboard LeftControl) */
    HID_LI_USAGE_MIN(1),
    0xE0,
    /* USAGE_MAXIMUM (Keyboard Right GUI) */
    HID_LI_USAGE_MAX(1),
    0xE7,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1),
    0x01,

    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE,
    0x01,
    /* REPORT_COUNT (8) */
    HID_GI_REPORT_COUNT,
    0x08,
    /* INPUT (Data,Var,Abs) */
    HID_MI_INPUT,
    0x02,

    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* REPORT_SIZE (8) */
    HID_GI_REPORT_SIZE,
    0x08,
    /* REPORT_COUNT (1) */
    HID_GI_REPORT_COUNT,
    0x01,
    /* INPUT (Cnst,Var,Abs) */
    HID_MI_INPUT,
    0x03,

    /* USAGE_PAGE (Keypad) */
    HID_GI_USAGE_PAGE,
    USAGE_GEN_DESKTOP_KEYPAD,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (0xFF) */
    HID_GI_LOGICAL_MAX(1),
    0xFF,
    /* USAGE_MINIMUM (Reserved) */
    HID_LI_USAGE_MIN(1),
    0x00,
    /* USAGE_MAXIMUM (Keyboard Application) */
    HID_LI_USAGE_MAX(1),
    0xFF,
    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE,
    0x08,
    /* REPORT_COUNT (ZMK_HID_KEYPAD_NKRO_SIZE) */
    HID_GI_REPORT_COUNT,
    ZMK_HID_KEYPAD_NKRO_SIZE,
    /* INPUT (Data,Ary,Abs) */
    HID_MI_INPUT,
    0x00,

    /* END_COLLECTION */
    HID_MI_COLLECTION_END,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE,
    0x0C,
    /* USAGE (Consumer Control) */
    HID_LI_USAGE,
    0x01,
    /* Consumer Page */
    HID_MI_COLLECTION,
    COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID,
    0x02,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE,
    0x0C,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1),
    0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1),
    0xFF,
    HID_LI_USAGE_MIN(1),
    0x00,
    /* USAGE_MAXIMUM (Keyboard Application) */
    HID_LI_USAGE_MAX(1),
    0xFF,
    /* INPUT (Data,Ary,Abs) */
    /* REPORT_SIZE (8) */
    HID_GI_REPORT_SIZE,
    0x08,
    /* REPORT_COUNT (ZMK_HID_CONSUMER_NKRO_SIZE) */
    HID_GI_REPORT_COUNT,
    ZMK_HID_CONSUMER_NKRO_SIZE,
    HID_MI_INPUT,
    0x00,
    /* END COLLECTION */
    HID_MI_COLLECTION_END,
};

// struct zmk_hid_boot_report
// {
//     u8_t modifiers;
//     u8_t _unused;
//     u8_t keys[6];
// } __packed;

struct zmk_hid_keypad_report_body {
    zmk_mod_flags modifiers;
    u8_t _reserved;
    u8_t keys[ZMK_HID_KEYPAD_NKRO_SIZE];
} __packed;

struct zmk_hid_keypad_report {
    u8_t report_id;
    struct zmk_hid_keypad_report_body body;
} __packed;

struct zmk_hid_consumer_report_body {
    u8_t keys[ZMK_HID_CONSUMER_NKRO_SIZE];
} __packed;

struct zmk_hid_consumer_report {
    u8_t report_id;
    struct zmk_hid_consumer_report_body body;
} __packed;

int zmk_hid_register_mod(zmk_mod modifier);
int zmk_hid_unregister_mod(zmk_mod modifier);
int zmk_hid_implicit_modifiers_press(zmk_mod_flags implicit_modifiers);
int zmk_hid_implicit_modifiers_release();
int zmk_hid_keypad_press(zmk_key key);
int zmk_hid_keypad_release(zmk_key key);
void zmk_hid_keypad_clear();

int zmk_hid_consumer_press(zmk_key key);
int zmk_hid_consumer_release(zmk_key key);
void zmk_hid_consumer_clear();

struct zmk_hid_keypad_report *zmk_hid_get_keypad_report();
struct zmk_hid_consumer_report *zmk_hid_get_consumer_report();
