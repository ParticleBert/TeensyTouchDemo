#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioControlSGTL5000      	sgtl5000;
AudioSynthWaveformModulated waveformMod1; // WaveformMod 1
AudioSynthWaveformModulated	waveformMod2; // WaveformMod 2
AudioEffectWaveshaper       waveshape1;  // Waveshaper 1
AudioEffectEnvelope         envelope1;    // Envelope 1
AudioSynthNoiseWhite		    noise1;       // Noise 1
AudioMixer4					        mixer1;       // Mixer 1
AudioFilterStateVariable    filter1;      // Filter 1
AudioSynthWaveformSine      sine1;        // Sine (Test)
AudioMixer4               	mixer2;       // Mixer 2
AudioAmplifier              amp1;         // Amp 1
AudioAmplifier              amp2;         // Amp 2
AudioAmplifier              amp3;         // Amp 3
AudioSynthWaveformDc        dc1;
AudioEffectMultiply         multiply1;    // Multiply
AudioEffectReverb           reverb1;      // Reverb
AudioOutputI2S              i2saudio;     // Output
AudioOutputAnalog           dac1;         // Output
// Connections
AudioConnection             patchCord13(waveformMod1, amp3);
AudioConnection             patchCord14(waveformMod1, envelope1);
AudioConnection             patchCord15(amp3, 0, waveformMod2, 0);
AudioConnection             patchCord39(envelope1, amp1);
AudioConnection             patchCord37(envelope1, amp2);


AudioConnection				      patchCord5(waveformMod2, 0, mixer1, 0);	// waveformMod 1 in channel 0
AudioConnection				      patchCord4(noise1, 0, mixer1, 1);		// noise in channel 1

// Mixer 1 and Amp 2 to Filter 1
AudioConnection             patchCord12(mixer1, 0, filter1, 0);
AudioConnection             patchCord35(amp2, 0, filter1, 0);

// Waveshape, Ladder and TestSine to Mixer 2
AudioConnection             patchCord20(filter1, 1, mixer2, 1);
AudioConnection             patchCord30(filter1, 0, waveshape1, 0);
AudioConnection             patchCord40(waveshape1, 0, mixer2, 0);
AudioConnection           	patchCord1(sine1, 0, mixer2, 2);

// Mixer 2 and Amp 1 to Multiply
AudioConnection             patchCord9(mixer2, 0, multiply1, 0);
AudioConnection             patchCord11(dc1, 0, multiply1, 1);
// AudioConnection             patchCord10(amp1, 0, multiply1, 1);

// Multiply to Reverb
AudioConnection             patchCord8(multiply1, reverb1);

// Reverb1 to DAC and I2S
AudioConnection             patchCord3(reverb1, 0, i2saudio, 0);
AudioConnection             patchCord7(reverb1, 0, i2saudio, 1);
AudioConnection             patchCord6(reverb1, dac1);

// GUItool: end automatically generated code

// GUItool: begin automatically generated code
/*
AudioSynthWaveformModulated waveformMod2;   //xy=244,683
AudioAmplifier           amp3;           //xy=266,546
AudioSynthNoiseWhite     noise1;         //xy=407,520
AudioSynthWaveformModulated waveformMod1;   //xy=433,432
AudioMixer4              mixer1;         //xy=592,527
AudioAmplifier           amp2;           //xy=799,566
AudioFilterLadder        ladder1;        //xy=800,518
AudioEffectEnvelope      envelope1;      //xy=952,688
AudioEffectWaveshaper    waveshape1;     //xy=956,468
AudioMixer4              mixer2;         //xy=1085,524
AudioAmplifier           amp1;           //xy=1142,613
AudioEffectMultiply      multiply1;      //xy=1280,530
AudioEffectReverb        reverb1;        //xy=1427,530
AudioOutputAnalog        dac1;           //xy=1554,530
AudioConnection          patchCord1(waveformMod2, envelope1);
AudioConnection          patchCord2(waveformMod2, amp3);
AudioConnection          patchCord3(amp3, 0, waveformMod1, 0);
AudioConnection          patchCord4(noise1, 0, mixer1, 1);
AudioConnection          patchCord5(waveformMod1, 0, mixer1, 0);
AudioConnection          patchCord6(mixer1, 0, ladder1, 0);
AudioConnection          patchCord7(amp2, 0, ladder1, 1);
AudioConnection          patchCord8(ladder1, waveshape1);
AudioConnection          patchCord9(ladder1, 0, mixer2, 1);
AudioConnection          patchCord10(envelope1, amp1);
AudioConnection          patchCord11(envelope1, amp2);
AudioConnection          patchCord12(waveshape1, 0, mixer2, 0);
AudioConnection          patchCord13(mixer2, 0, multiply1, 0);
AudioConnection          patchCord14(amp1, 0, multiply1, 1);
AudioConnection          patchCord15(multiply1, reverb1);
AudioConnection          patchCord16(reverb1, dac1);
*/
// GUItool: end automatically generated code

void setup() {
  // Init serial
  Serial.begin(9600);
  // Init the CODEC
  sgtl5000.enable();
  sgtl5000.volume(0.5);
  // Audio Memory
  AudioMemory(20);

  waveformMod1.begin(0.3, 200, WAVEFORM_TRIANGLE);

  waveformMod2.begin(0.3, 150, WAVEFORM_SQUARE);
  noise1.amplitude(0.3);

  mixer1.gain(0,1);
  mixer1.gain(1,1);

  sine1.frequency(440);
  sine1.amplitude(0.3);
  mixer2.gain(0,1);
  mixer2.gain(1,1);
  dc1.amplitude(1);
  // Reverb
  reverb1.reverbTime(0.2);
  envelope1.delay(200);
}

void loop() {
  // Read the potis
  float value_a7 = (float)analogRead(A7) / 1023;  // Norm to the range from 0 to 1
  float value_a6 = (float)analogRead(A6) / 1023;  // Norm to the range from 0 to 1
  float filter_cutoff = value_a7 * 20000;                    // Convert to Hertz (20kHz maximum)
  float filter_reso = value_a6 * 5;                           // TODO Lower Limit of the Reso is 0.7
                                                              // TODO The Filter amplifies at resos > 0.707. The inpus has to attenuated.
  // Set the values
  filter1.frequency(filter_cutoff);
  filter1.resonance(filter_reso);
  // Serial.println(value_a7);
  // delay(1);

  envelope1.noteOn();
  delay(1);
  envelope1.noteOn();
  delay(1);
  
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
