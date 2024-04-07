
#include <stdio.h>
#include "pico/stdlib.h"
#include "classifier/ei_run_classifier.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"


static bool debug_nn = false; 

const uint LED_PIN = 25;

float readAxisAccelation (int adc_n) {
    adc_select_input(adc_n);
    unsigned int axis_raw = 0;
    axis_raw=adc_read();
    float axis_g=axis_raw*16; 
    return axis_g;
}

int main()
{
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
    
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
    
    if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3) {
        ei_printf("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes)\n");
        return 1;
    }
    
    while (true){
        
        ei_printf("\nStarting inferencing in 2 seconds...\n");
        sleep_ms(2000);
        gpio_put(LED_PIN, 1);
        ei_printf("Sampling...\n");

        
        float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

        for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
            
            uint64_t next_tick = ei_read_timer_us() + (EI_CLASSIFIER_INTERVAL_MS * 1000);
            
            buffer[ix] = readAxisAccelation (0);
            buffer[ix + 1] = readAxisAccelation (1);
            buffer[ix + 2] = readAxisAccelation (2);

          

            sleep_us(next_tick - ei_read_timer_us());
        }

        
        signal_t signal;
        int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
        if (err != 0) {
            ei_printf("Failed to create signal from buffer (%d)\n", err);
            return 1;
        }

        
        ei_impulse_result_t result = { 0 };

        err = run_classifier(&signal, &result, debug_nn);
        if (err != EI_IMPULSE_OK) {
            ei_printf("ERR: Failed to run classifier (%d)\n", err);
            return 1;
        }

        
        ei_printf("Predictions ");
        ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
            result.timing.dsp, result.timing.classification, result.timing.anomaly);
        ei_printf(": \n");
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
        }
    #if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf("    anomaly score: %.3f\n", result.anomaly);
    #endif
    gpio_put(LED_PIN, 0);
    }

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_ACCELEROMETER
#error "Invalid model for current sensor"
#endif
return 0;
}