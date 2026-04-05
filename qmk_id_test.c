/*
   Copyright 2021 Thomas Weißschuh <thomas@t-8ch.de>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#define main original_main
#include "qmk_id.c"
#undef main

int main() {
    struct testcase {
        char        description[100];
        int         expected_ret;
        const char *expected_output;
        size_t      report_size;
        uint8_t     report[100];
    };

    // clang-format off
    struct testcase testcases[] = {
        {"empty input",                  -EIO, NULL,              0,  {0}},
        // console (Teensy-style, 0xFF310074)
        {"console: basic descriptor",             1,    ep_output_console, 7,  {0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}},
        {"console: different usage page",         0,    NULL,              7,  {0x06, 0x30, 0xFF, 0x09, 0x74, 0xA1, 0x01}},
        {"console: different usage",              0,    NULL,              7,  {0x06, 0x31, 0xFF, 0x09, 0x73, 0xA1, 0x01}},
        {"console: empty long items",             1,    ep_output_console, 10, {0xFE, 0X00, 0xF0, 0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}},
        {"console: long items",                   1,    ep_output_console, 11, {0xFE, 0X01, 0xF0, 0x00, 0x06, 0x31, 0xFF, 0x09, 0x74, 0xA1, 0x01}},
        // raw HID (0xFF600061)
        {"raw hid: basic descriptor",             1,    ep_output_raw_hid, 7,  {0x06, 0x60, 0xFF, 0x09, 0x61, 0xA1, 0x01}},
        {"raw hid: different usage page",         0,    NULL,              7,  {0x06, 0x31, 0xFF, 0x09, 0x61, 0xA1, 0x01}},
        {"raw hid: different usage",              0,    NULL,              7,  {0x06, 0x60, 0xFF, 0x09, 0x60, 0xA1, 0x01}},
        // XAP (0xFF510058)
        {"xap: basic descriptor",                 1,    ep_output_xap,     7,  {0x06, 0x51, 0xFF, 0x09, 0x58, 0xA1, 0x01}},
        {"xap: different usage page",             0,    NULL,              7,  {0x06, 0x31, 0xFF, 0x09, 0x58, 0xA1, 0x01}},
        {"xap: different usage",                  0,    NULL,              7,  {0x06, 0x51, 0xFF, 0x09, 0x57, 0xA1, 0x01}},
    };
    // clang-format on

    int num_testcases = ARRAY_SIZE(testcases);

    printf("TAP version 13\n");
    printf("1..%d\n", num_testcases);

    int failed = 0;

    for (int i = 0; i < num_testcases; i++) {
        struct testcase            tc       = testcases[i];
        const struct qmk_endpoint *endpoint = NULL;
        int                        ret      = find_qmk_endpoint(tc.report, tc.report_size, &endpoint);
        const char                *output   = endpoint ? endpoint->output : NULL;

        if (ret != tc.expected_ret) {
            failed++;
            printf("not ok %d - %s\n  result %d != expected %d\n", i + 1, tc.description, ret, tc.expected_ret);
        } else if (output != tc.expected_output) {
            failed++;
            printf("not ok %d - %s\n  output '%s' != expected '%s'\n", i + 1, tc.description, output, tc.expected_output);
        } else {
            printf("ok %d - %s\n", i + 1, tc.description);
        }
    }

    return failed;
}
