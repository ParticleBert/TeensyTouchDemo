#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

#define MODULATOR_FREQ_LOWER 5    // This parameter sets the lower frequency (in Hertz) for the modulating oscillator
#define MODULATOR_FREQ_UPPER 200  // This parameter sets the upper frequency (in Hertz) for the modulating oscillator
                                  // TODO: What is the exact range of the AudioSynthWaveformModulated class?

// GUItool: begin automatically generated code
AudioSynthWaveformModulated waveformMod1;   //xy=165.57147216796875,267.857177734375
AudioAmplifier           amp3;           //xy=367.4285888671875,216.85711669921875
AudioEffectEnvelope      envelope1;      //xy=375.4285888671875,367.8571472167969
AudioSynthWaveformModulated waveformMod2;   //xy=531.0000152587891,224
AudioSynthNoiseWhite     noise1;         //xy=552.1428985595703,264.71429443359375
AudioMixer4              mixer1;         //xy=716.0000152587891,271
AudioAmplifier           amp2;           //xy=717.7142486572266,323
AudioFilterStateVariable filter1;        //xy=895.0000152587891,277
AudioEffectWaveshaper    waveshape1;     //xy=1047.2857360839844,233.28571319580078
AudioAmplifier           amp1;           //xy=1197.857177734375,362.7142639160156
AudioMixer4              mixer2;         //xy=1202.000015258789,285
AudioMixer4             mixer3;
AudioEffectMultiply      multiply1;      //xy=1397.000015258789,291
AudioEffectReverb        reverb1;        //xy=1544.000015258789,291
AudioOutputAnalog        dac2; //xy=1712.4285926818848,239.57141780853271
AudioOutputI2S           i2s1;           //xy=1716.8571968078613,339.1428623199463
AudioConnection          patchCord1(waveformMod1, envelope1);
AudioConnection          patchCord2(waveformMod1, amp3);
AudioConnection          patchCord3(amp3, 0, waveformMod2, 0);
AudioConnection          patchCord4(envelope1, amp1);
AudioConnection         patchCord18(envelope1, 0, filter1, 1);
// AudioConnection          patchCord5(envelope1, amp2);
AudioConnection          patchCord6(waveformMod2, 0, mixer1, 0);
AudioConnection          patchCord7(noise1, 0, mixer1, 1);
AudioConnection          patchCord8(mixer1, 0, filter1, 0);
// AudioConnection          patchCord9(amp2, 0, filter1, 1);
AudioConnection          patchCord10(filter1, 0, waveshape1, 0);
AudioConnection          patchCord11(filter1, 1, mixer2, 1);
AudioConnection          patchCord12(waveshape1, 0, mixer2, 0);
AudioConnection          patchCord14(mixer2, 0, multiply1, 0);
AudioConnection          patchCord16(multiply1, 0, mixer3, 0);
AudioConnection          patchCord15(multiply1, reverb1);
AudioConnection         patchCord19(reverb1, 0, mixer3, 1);
AudioConnection           patchCord17(mixer3, 0, dac2, 0);
// AudioConnection          patchCord16(reverb1, dac2);
AudioConnection          patchCord20(mixer3, 0, i2s1, 0);
AudioConnection          patchCord21(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1710.4286041259766,391.5714416503906

// Debug
AudioSynthWaveformDc      dc1;
AudioConnection          patchCord13(envelope1, 0, multiply1, 1);
// AudioConnection           patchCord13(dc1, 0, multiply1, 1);
// GUItool: end automatically generated code
Bounce button0 = Bounce(8, 15);

  int req_noteoff = 0;

void setup() {
  pinMode(8, INPUT_PULLUP);   // This pin triggers the envelope
  
  // Init serial
  Serial.begin(9600);
  // Init the CODEC
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  // Audio Memory
  AudioMemory(10);
  amp3.gain(1);
  amp2.gain(1);
  amp1.gain(1);

  waveformMod1.begin(0.3, 200, WAVEFORM_TRIANGLE);
  waveformMod2.begin(0.3, 150, WAVEFORM_SQUARE);
  noise1.amplitude(0.3);

  mixer1.gain(0,1);
  mixer1.gain(1,0.5);

  // sine1.frequency(440);
  // sine1.amplitude(0.3);
  mixer2.gain(0,1);
  mixer2.gain(1,1);
  dc1.amplitude(1);
  mixer3.gain(0,0.9); // Dry
  mixer3.gain(0,0.7); // Reverb
  // Reverb
  reverb1.reverbTime(3);
  envelope1.attack(200);
  envelope1.release(200);
}

void loop() {

  
  button0.update();
  // Read the potis
  float value_a7 = (float)analogRead(A7) / 1023;  // Norm to the range from 0 to 1
  float value_a6 = (float)analogRead(A6) / 1023;  // Norm to the range from 0 to 1
  float value_a3 = (float)analogRead(A3) / 1023;
  float value_a2 = (float)analogRead(A2) / 1023;
  float value_a1 = (float)analogRead(A1) / 1023;
  
  float filter_cutoff = value_a7 * 5000;                    // Convert to Hertz (20kHz maximum)
  float filter_reso = value_a6 * 5;                           // TODO Lower Limit of the Reso is 0.7
                                                               // TODO The Filter amplifies at resos > 0.707. The inpus has to attenuated.
                                                              // But at the moment it's OK.
  float freq1 = value_a3 * MODULATOR_FREQ_UPPER + MODULATOR_FREQ_LOWER;                  // HINT This is the frequency for the modulating oscillator.
                                                  // HINT Use ranges from 1Hz up to the audio range.
  float attack1 = value_a2 * 2000;
  float release1 = value_a1 * 2000;
  
  // Set the values
  filter1.frequency(filter_cutoff);
  filter1.resonance(filter_reso);
  waveformMod1.frequency(freq1);
  envelope1.attack(attack1);
  envelope1.sustain(1);
  envelope1.release(release1);
  // Serial.println(value_a7);
  // delay(1);

  if (button0.fallingEdge() ) {
      envelope1.noteOn();
      Serial.println("Envelope On");
  }
  
  if (button0.risingEdge() ) {    // Button is released
      if(envelope1.isSustain() == false) // env1 is not (yet?) in the sustain phase
      {
        Serial.println("Noteoff requested for later");
        req_noteoff = 1;  // Save the NoteOff for later.
      }
      else
      {
        Serial.println("Noteoff send");
        envelope1.noteOff();
      }

  }

  // Now, check periodically while the envelope is running...
  if( (req_noteoff == 1) && (envelope1.isSustain() == true) )
  {
      Serial.println("Noteoff request fulfilled");
      envelope1.noteOff();  // Send the NoteOff
      req_noteoff = 0;      // Delete the note
  }

// VCO 01
// waveformMod1 (vco) select waveform
// waveformMod1 (vco) init freq (master tuning)
// waveformMod1 (vco) freq knob
// waveformMod1 (vco) freq cv input
// amp3 (vco) amount of vco2 applied to input

// VCO 02 (CLOCK)
// waveformMod2 (vco) select waveform
// waveformMod2 (vco) init freq (master tuning)

// MIX WAVE AND NOISE
// mixer1 (waveform+noise) set gains

// FILTER
// ladder1 init freq cut-off
// ladder1 cut-off knob       DONE
// ladder1 res knob           DONE
// amp2 attenuation (amount of envelope applied on cut-off)

// DISTORTION
// waveshape1 (distortion) amount 
// mixer2 (waveshape+clean) set gains

// ENVELOPE
// envelope1 attack init
// envelope1 attack knob
// envelope1 release init
// envelope1 release knob

// VCA
// multiply1 (vca) init volume
// amp1 amount of envelope in

}
