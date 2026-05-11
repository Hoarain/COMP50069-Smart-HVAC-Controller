#include <Arduino.h>
#include <esp_task_wdt.h>

#include "sensors.h"
#include "control.h"
#include "safety.h"
#include "logging.h"

HVACData hvacData;
SemaphoreHandle_t dataMutex;

void sensorTask(void *parameter) {
    while (true) {
        if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
            readSensors(hvacData);
            xSemaphoreGive(dataMutex);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void safetyTask(void *parameter) {
    while (true) {
        if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
            checkSafety(hvacData);
            xSemaphoreGive(dataMutex);
        }

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void controlTask(void *parameter) {
    while (true) {
        if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
            updateControl(hvacData);
            xSemaphoreGive(dataMutex);
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void loggingTask(void *parameter) {
    while (true) {
        if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
            printStatus(hvacData);
            xSemaphoreGive(dataMutex);
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void setup() {
    Serial.begin(115200);

    esp_task_wdt_config_t wdt_config = {
        .timeout_ms = 5000,
        .idle_core_mask = (1 << portNUM_PROCESSORS) - 1,
        .trigger_panic = true
    };

    esp_task_wdt_init(&wdt_config);
    esp_task_wdt_add(NULL);

    hvacData.temperature = 0;
    hvacData.setpoint = 25;
    hvacData.fanOn = false;
    hvacData.emergency = false;
    hvacData.sensorFault = false;

    initSensors();
    initControl();
    initSafety();

    dataMutex = xSemaphoreCreateMutex();

    if (dataMutex == NULL) {
        Serial.println("Mutex creation failed!");
        while (true);
    }

    xTaskCreate(sensorTask, "Sensor Task", 4096, NULL, 2, NULL);
    xTaskCreate(safetyTask, "Safety Task", 4096, NULL, 4, NULL);
    xTaskCreate(controlTask, "Control Task", 4096, NULL, 3, NULL);
    xTaskCreate(loggingTask, "Logging Task", 4096, NULL, 1, NULL);

    Serial.println("FreeRTOS Industrial Smart HVAC Controller Started");
}

void loop() {
    esp_task_wdt_reset();
}