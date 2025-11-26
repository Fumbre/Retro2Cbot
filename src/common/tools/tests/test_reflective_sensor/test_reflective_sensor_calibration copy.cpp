// 8-sensor diagnostic test for Arduino Nano (A0..A7)
// Samples for durationSeconds and prints:
//  - per-sensor mean, min, max, stddev
//  - overall mean and which sensor had highest average
//  - CSV of per-sensor averages for easy import
//
// Usage:
// 1) Upload to your Nano (close Serial Plotter first).
// 2) Open Serial Monitor at 115200 baud.
// 3) The test will run automatically once the board resets.

#include "test_reflective_sensor_calibration.h"


const int pins[8] = {
  A0, // RS_D8 -> S1
  A1, // RS_D7 -> S2
  A2, // RS_D6 -> S3
  A3, // RS_D5 -> S4
  A4, // RS_D4 -> S5
  A5, // RS_D3 -> S6
  A6, // RS_D2 -> S7
  A7  // RS_D1 -> S8
};

const unsigned long durationSeconds = 5UL; // test duration
const unsigned int sampleIntervalMs = 10;   // sample every 10 ms (~100 Hz)
                                             // adjust if you want fewer/more samples

// Stats per sensor using Welford's algorithm

void setupRs() {
  Serial.begin(115200);
  while (!Serial) { /* wait for serial */ }
  Serial.println();
  Serial.println(F("=== 8-Sensor Diagnostic Test ==="));
  Serial.print("Duration (s): ");
  Serial.println(durationSeconds);
  Serial.print("Sample interval (ms): ");
  Serial.println(sampleIntervalMs);
  Serial.println(F("Sampling will start in 2 seconds..."));
  delay(2000);
}

Stats stats[8];

void loopRs() {
  // Reset stats
  for (int i = 0; i < 8; ++i) {
    stats[i] = Stats();
  }

  unsigned long start = millis();
  unsigned long endTime = start + durationSeconds * 1000UL;
  unsigned long nextSample = millis();

  // Optional: print periodic progress
  unsigned long lastProgressPrint = 0;

  while (millis() < endTime) {
    unsigned long now = millis();
    if (now >= nextSample) {
      // Read and update stats
      for (int i = 0; i < 8; ++i) {
        int v = analogRead(pins[i]);
        stats[i].update(v);
      }
      nextSample += sampleIntervalMs;
    }

    // Print progress every 5 seconds
    if (now - lastProgressPrint >= 5000UL) {
      unsigned long elapsed = now - start;
      unsigned long remaining = (endTime > now) ? (endTime - now) / 1000UL : 0;
      Serial.print("Elapsed: ");
      Serial.print(elapsed / 1000UL);
      Serial.print(" s, remaining ~ ");
      Serial.print(remaining);
      Serial.println(" s");
      lastProgressPrint = now;
    }
    // small yield to let USB keep up
    delay(0);
  }

  // Done sampling — print results
  Serial.println();
  Serial.println(F("=== Test Complete — Summary ==="));
  unsigned long totalSamples = stats[0].count; // same for all sensors
  Serial.print("Samples per sensor: ");
  Serial.println(totalSamples);

  // CSV header of averages
  Serial.println();
  Serial.print("CSV_AVERAGES,"); // tag for easy find
  for (int i = 0; i < 8; ++i) {
    Serial.print("S");
    Serial.print(i + 1);
    Serial.print((i < 7) ? "," : "\n");
  }

  // CSV line with averages (rounded)
  Serial.print("CSV_VALUES,");
  double overallSum = 0.0;
  int bestSensor = 0;
  double bestMean = stats[0].mean;
  for (int i = 0; i < 8; ++i) {
    double m = stats[i].mean;
    overallSum += m;
    if (m > bestMean) { bestMean = m; bestSensor = i; }
    Serial.print((long)round(m));
    Serial.print((i < 7) ? "," : "\n");
  }
  double overallMean = overallSum / 8.0;

  Serial.println();
  // Human readable per-sensor stats
  for (int i = 0; i < 8; ++i) {
    Serial.print("S");
    Serial.print(i + 1);
    Serial.print(": mean=");
    Serial.print(stats[i].mean, 2);
    Serial.print(" min=");
    Serial.print(stats[i].minimum);
    Serial.print(" max=");
    Serial.print(stats[i].maximum);
    Serial.print(" stddev=");
    Serial.print(stats[i].stddev(), 2);
    Serial.println();
  }

  Serial.println();
  Serial.print("Overall mean (all sensors): ");
  Serial.println(overallMean, 2);
  Serial.print("Sensor with highest mean: S");
  Serial.print(bestSensor + 1);
  Serial.print(" (mean=");
  Serial.print(bestMean, 2);
  Serial.println(")");

  // Extra useful info: activity (how many readings above simple threshold)
  // Choose threshold = midpoint of sensor range for each sensor (mean of min/max)
  Serial.println();
  Serial.println("Activity summary (estimations):");
  for (int i = 0; i < 8; ++i) {
    int thresh = (stats[i].minimum + stats[i].maximum) / 2;
    // We'll do a quick pass to count values > threshold by re-sampling briefly
    // (this is optional and cheap: 100 samples)
    int above = 0;
    const int quickSamples = 100;
    for (int s = 0; s < quickSamples; ++s) {
      int v = analogRead(pins[i]);
      if (v > thresh) above++;
      delay(2);
    }
    float pct = (above * 100.0) / quickSamples;
    Serial.print("S");
    Serial.print(i + 1);
    Serial.print(": thresh=");
    Serial.print(thresh);
    Serial.print(" quickAbove%=");
    Serial.print(pct, 1);
    Serial.println("%");
  }

  Serial.println();
  Serial.println(F("=== End of report ==="));
  Serial.println();

  // Done — halt (or delay long). To re-run, press reset or power-cycle.
}
