#include <Bounce.h>
#include <usb_names.h>

#define NUM_BUTTONS 13

// Button pins
const int buttonPins[NUM_BUTTONS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15};

// MIDI note number for the lowest button
const int baseNote = 36; // C2

// Button objects
Bounce buttons[NUM_BUTTONS] = {
  Bounce(buttonPins[0], 5),
  Bounce(buttonPins[1], 5),
  Bounce(buttonPins[2], 5),
  Bounce(buttonPins[3], 5),
  Bounce(buttonPins[4], 5),
  Bounce(buttonPins[5], 5),
  Bounce(buttonPins[6], 5),
  Bounce(buttonPins[7], 5),
  Bounce(buttonPins[8], 5),
  Bounce(buttonPins[9], 5),
  Bounce(buttonPins[10], 5),
  Bounce(buttonPins[11], 5),
  Bounce(buttonPins[12], 5)
};

void setup() {
  for (int i = 2; i <= 15; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.begin();
}
void loop() {
  usbMIDI.read();

  // Update button states
  for (int i = 0; i < NUM_BUTTONS; i++) {
    buttons[i].update();
  }

  // Send MIDI messages based on button edges
  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (buttons[i].fallingEdge()) {
      // Button is pressed, send MIDI note-on message
      usbMIDI.sendNoteOn(baseNote + i, 99, 1);
    }
    if (buttons[i].risingEdge()) {
      // Button is released, send MIDI note-off message
      usbMIDI.sendNoteOff(baseNote + i, 0, 1);
    }
  }
}

void OnNoteOn(byte channel, byte note, byte velocity) {
  // Handle incoming MIDI note-on messages
  // (optional: add your own code here)
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  // Handle incoming MIDI note-off messages
  // (optional: add your own code here)
}
