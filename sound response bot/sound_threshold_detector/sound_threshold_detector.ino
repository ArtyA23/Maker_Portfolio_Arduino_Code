const int micPin = A0;

// ---- Timing ----
const unsigned long windowDuration = 10; // ms
unsigned long windowStartTime = 0;

// ---- Baseline tracking ----
float baseline = 300;        // initial guess (close to what you observed)
float baselineAlpha = 0.01;  // how slowly baseline adapts
bool freezeBaseline = false;

// ---- Window accumulation ----
unsigned long sampleCount = 0;
unsigned long deviationSum = 0;

// ---- Threshold ----
const int deviationThreshold = 50; // YOU tune this

void setup() {
  Serial.begin(9600);
  windowStartTime = millis();
}

void loop() {
  // 1. Read microphone
  int micValue = analogRead(micPin);

  // 2. Compute deviation from baseline
  int deviation = abs(micValue - baseline);

  // 3. Accumulate deviation inside window
  deviationSum += deviation;
  sampleCount++;

  // 4. Check if window is over
  unsigned long now = millis();
  if (now - windowStartTime >= windowDuration) {

    // 5. Compute window average deviation
    float windowAvg = (float)deviationSum / sampleCount;

    // 6. Event detection
    if (windowAvg > deviationThreshold) {
      Serial.print("EVENT: ");
      Serial.println(windowAvg);
      freezeBaseline = true;
    } else {
      freezeBaseline = false;
    }

    // 7. Update baseline (slowly, only if not frozen)
    if (!freezeBaseline) {
      baseline = (1.0 - baselineAlpha) * baseline
                 + baselineAlpha * micValue;
    }

    // 8. Reset window
    deviationSum = 0;
    sampleCount = 0;
    windowStartTime = now;
  }
}

