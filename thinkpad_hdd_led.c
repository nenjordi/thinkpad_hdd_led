/*
Copyright (c) 2013, Jordi Ortiz
All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The source code of this package was created by Dan Stahlke (dan@stahlke.org) under BSD license and I have only encapsulated it for Arch.

This script flashes the ThinkPad light when there is hard drive activity.
Then run as root.

Script by Dan Stahlke, dan@stahlke.org.  BSD license.  No warranty.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// This is the interface to the LED.
static const char *led_fn = "/proc/acpi/ibm/led";
// This defines the check and flash intervals, in microseconds.
static const int check_interval = 200000; // 5 Hz
static const int flash_off_interval = 40000; // flash at 20 Hz, 20% duty cycle
static const int flash_on_interval  = 10000;

void set_led(int new_status) {
    int led_id = 0;
    FILE *fh = fopen(led_fn, "w");
    if (!fh) {
        fprintf(stderr, "Could not open %s, aborting.\n", led_fn);
        abort();
    }
    fprintf(fh, "%d %s\n", led_id, new_status ? "on" : "off");
    fclose(fh);
}

// Get total accumulated disk read and write counts.
// The idea for this came from an answer to
// http://superuser.com/questions/362694/use-caps-lock-led-as-hdd-led-or-custom-indicator
long get_pgpg_stats() {
    FILE *fh = fopen("/proc/vmstat", "r");
    if (!fh) {
        fprintf(stderr, "Could not open /proc/vmstat, aborting.\n");
        abort();
    }
    char buf[100];
    long pgpgin=0, pgpgout=0;
    while (fgets(buf, 100, fh)) {
        if (strstr(buf, "pgpgin")) {
            if (1 != sscanf(buf, "pgpgin %ld\n", &pgpgin)) {
                fprintf(stderr, "Could not parse vmstat line, aborting.\n");
                abort();
            }
        }
        if (strstr(buf, "pgpgout")) {
            if (1 != sscanf(buf, "pgpgout %ld\n", &pgpgout)) {
                fprintf(stderr, "Could not parse vmstat line, aborting.\n");
                abort();
            }
        }
    }
    if (!pgpgin || !pgpgout) {
        fprintf(stderr, "Could not find pgpg info in vmstat, aborting.\n");
        abort();
    }
    fclose(fh);
    return pgpgin + pgpgout;
}

int main() {
    long last_stat = get_pgpg_stats();
    for (;;) {
        while (get_pgpg_stats() != last_stat) {
            last_stat = get_pgpg_stats();
            set_led(1);
            usleep(flash_off_interval);
            set_led(0);
            usleep(flash_on_interval);
        }
        usleep(check_interval);
    }
}
