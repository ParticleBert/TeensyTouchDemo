#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioControlSGTL5000      	sgtl5000;
AudioOutputI2S            	i2saudio;
AudioSynthWaveformSine    	sine1;          //xy=1324.9999999999998,366.66666666666663
AudioSynthWaveformModulated	waveformMod1;
AudioSynthNoiseWhite		noise1;
AudioOutputAnalog         	dac1;           //xy=1590,354
AudioEffectReverb         	reverb1;
AudioMixer4					mixer1;
AudioMixer4               	mixer2;


AudioConnection           	patchCord3(reverb1, i2saudio);
// Mixer 1
AudioConnection				patchCord5(wafeformMod1, 0, mixer1, 0);	// waveformMod 1 in channel 0
AudioConnection				patchCord4(noise1, 0, mixer1, 1);		// noise in channel 1
// Mixer 2
AudioConnection           	patchCord1(sine1, 0, mixer2, 0);		// Input
AudioConnection           	patchCord2(mixer2, 0, reverb1, 0);		// Output	

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
  sgtl5000.enable();
  sgtl5000.volume(0.5);
  AudioMemory(20);
  // Sinewave
  sine1.frequency(440);
  sine1.amplitude(0.3);
  // Mixer 2
  mixer2.gain(0,1);
  // Reverb
  reverb1.reverbTime(0.2);
}

void loop() {
  
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
// ladder1 cut-off knob
// ladder1 res knob
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
