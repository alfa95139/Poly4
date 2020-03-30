
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       Voice1OscA;      //xy=198,50
AudioSynthWaveform       Voice1OscB;      //xy=194,109
AudioSynthWaveform       Voice2OscA;      //xy=130,233
AudioSynthWaveform       Voice2OscB;      //xy=129,282
AudioSynthWaveform       Voice3OscA;      //xy=143,426
AudioSynthWaveform       Voice3OscB;      //xy=143,467
AudioSynthWaveform       Voice4OscA;      //xy=162,586
AudioSynthWaveform       Voice4OscB;      //xy=161,638
AudioSynthNoisePink      pinkNoiseGen;          //xy=132,350
AudioMixer4              Voice1Mixer;         //xy=389,110
AudioMixer4              Voice2Mixer;         //xy=385,258
AudioMixer4              Voice3Mixer;         //xy=384,424
AudioMixer4              Voice4Mixer;         //xy=387,567
AudioFilterStateVariable Voice1LPF12db;        //xy=557,116
AudioFilterStateVariable Voice2LPF12db;        //xy=560,265
AudioFilterStateVariable Voice3LPF12db;        //xy=577,431
AudioFilterStateVariable Voice4LPF12db;        //xy=577,573
AudioEffectEnvelope      Voice1ADSR;      //xy=752,104
AudioEffectEnvelope      Voice2ADSR;      //xy=757,252
AudioEffectEnvelope      Voice3ADSR;      //xy=760,417
AudioEffectEnvelope      Voice4ADSR;      //xy=773,560
AudioMixer4              OutMixer;         //xy=968,349
AudioOutputI2S           i2s1;           //xy=1114,348
AudioConnection          patchCord1(Voice2OscB, 0, Voice2Mixer, 1);
AudioConnection          patchCord2(Voice2OscA, 0, Voice2Mixer, 0);
AudioConnection          patchCord3(pinkNoiseGen, 0, Voice1Mixer, 2);
AudioConnection          patchCord4(pinkNoiseGen, 0, Voice2Mixer, 2);
AudioConnection          patchCord5(pinkNoiseGen, 0, Voice3Mixer, 2);
AudioConnection          patchCord6(pinkNoiseGen, 0, Voice4Mixer, 2);
AudioConnection          patchCord7(Voice3OscA, 0, Voice3Mixer, 0);
AudioConnection          patchCord8(Voice3OscB, 0, Voice3Mixer, 1);
AudioConnection          patchCord9(Voice4OscB, 0, Voice4Mixer, 1);
AudioConnection          patchCord10(Voice4OscA, 0, Voice4Mixer, 0);
AudioConnection          patchCord11(Voice1OscB, 0, Voice1Mixer, 1);
AudioConnection          patchCord12(Voice1OscA, 0, Voice1Mixer, 0);
AudioConnection          patchCord13(Voice3Mixer, 0, Voice3LPF12db, 0);
AudioConnection          patchCord14(Voice2Mixer, 0, Voice2LPF12db, 0);
AudioConnection          patchCord15(Voice4Mixer, 0, Voice4LPF12db, 0);
AudioConnection          patchCord16(Voice1Mixer, 0, Voice1LPF12db, 0);
AudioConnection          patchCord17(Voice1LPF12db, 0, Voice1ADSR, 0);
AudioConnection          patchCord18(Voice2LPF12db, 0, Voice2ADSR, 0);
AudioConnection          patchCord19(Voice3LPF12db, 0, Voice3ADSR, 0);
AudioConnection          patchCord20(Voice4LPF12db, 0, Voice4ADSR, 0);
AudioConnection          patchCord21(Voice1ADSR, 0, OutMixer, 0);
AudioConnection          patchCord22(Voice2ADSR, 0, OutMixer, 1);
AudioConnection          patchCord23(Voice3ADSR, 0, OutMixer, 2);
AudioConnection          patchCord24(Voice4ADSR, 0, OutMixer, 3);
AudioConnection          patchCord25(OutMixer, 0, i2s1, 0);
AudioConnection          patchCord26(OutMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=703,719
// GUItool: end automatically generated code

// GLOBAL VARIABLES
const byte NUM_OSC = 4; // Number of voices
const byte BUFFER = NUM_OSC + 1; 
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
byte latestNote = 0;
byte latestVelocity = 0;
int octave = 0;
const float DIV127 = (1.0 / 127.0);
float detuneFactor = 1;


void setup() {
  AudioMemory(20);
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);
  
  Voice1OscA.begin(WAVEFORM_SAWTOOTH);
  Voice1OscA.amplitude(0.75);
  Voice1OscA.frequency(82.41);
  Voice1OscA.pulseWidth(0.15);
  Voice1OscB.begin(WAVEFORM_SAWTOOTH);
  Voice1OscB.amplitude(0.75);
  Voice1OscB.frequency(123);
  Voice1OscB.pulseWidth(0.15);

  Voice2OscA.begin(WAVEFORM_SAWTOOTH);
  Voice2OscA.amplitude(0.75);
  Voice2OscA.frequency(82.41);
  Voice2OscA.pulseWidth(0.15);
  Voice2OscB.begin(WAVEFORM_SAWTOOTH);
  Voice2OscB.amplitude(0.75);
  Voice2OscB.frequency(123);
  Voice2OscB.pulseWidth(0.15);
  
  Voice3OscA.begin(WAVEFORM_SAWTOOTH);
  Voice3OscA.amplitude(0.75);
  Voice3OscA.frequency(82.41);
  Voice3OscA.pulseWidth(0.15);
  Voice3OscB.begin(WAVEFORM_SAWTOOTH);
  Voice3OscB.amplitude(0.75);
  Voice3OscB.frequency(123);
  Voice3OscB.pulseWidth(0.15);

  Voice4OscA.begin(WAVEFORM_SAWTOOTH);
  Voice4OscA.amplitude(0.75);
  Voice4OscA.frequency(82.41);
  Voice4OscA.pulseWidth(0.15);
  Voice4OscB.begin(WAVEFORM_SAWTOOTH);
  Voice4OscB.amplitude(0.75);
  Voice4OscB.frequency(123);
  Voice4OscB.pulseWidth(0.15);

  pinkNoiseGen.amplitude(1.0);

  Voice1Mixer.gain(0, 1.00);
  Voice1Mixer.gain(1, 1.00);
  Voice1Mixer.gain(2, 0.0);
  Voice2Mixer.gain(0, 1.0);
  Voice2Mixer.gain(1, 1.0);
  Voice2Mixer.gain(2, 0.0);
  Voice3Mixer.gain(0, 1.0);
  Voice3Mixer.gain(1, 1.0);
  Voice3Mixer.gain(2, 0.0);
  Voice4Mixer.gain(0, 1.0);
  Voice4Mixer.gain(1, 1.0);
  Voice4Mixer.gain(2, 0.0);
  
  Voice1ADSR.attack(0);
  Voice1ADSR.decay(0);
  Voice1ADSR.sustain(1);
  Voice1ADSR.release(1000);
  
  Voice2ADSR.attack(0);
  Voice2ADSR.decay(0);
  Voice2ADSR.sustain(1);
  Voice2ADSR.release(1000);
  
  Voice3ADSR.attack(0);
  Voice3ADSR.decay(0);
  Voice3ADSR.sustain(1);
  Voice3ADSR.release(1000);
  
  Voice4ADSR.attack(0);
  Voice4ADSR.decay(0);
  Voice4ADSR.sustain(1);
  Voice4ADSR.release(1000);

  OutMixer.gain(0, 0.25);
  OutMixer.gain(1, 0.25);
  OutMixer.gain(2, 0.25);
  OutMixer.gain(3, 0.25);
}

void loop() {
  // put your main code here, to run repeatedly:
   usbMIDI.read();
}



void myNoteOn(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    latestNote = note;
    latestVelocity = velocity;
    keyBuff(note, true);
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    keyBuff(note, false);
  }
}

// We are implementing a special resource buffer, each buffer has two components:
// a) the note that has to be played (note on)
// b) the "age" of that oscillator: this way we will know which oscillator to turn off 
// if and when more than NUM_OSC notes are played at the same time.
// location [0] to location [NUM_OSC] 
// location [0] is reserved to the NextAvailOsc pointer, while locations from [1] to [NUM_OSC] 
// map to physical SW oscillators each location contains the note that needs to be played


void keyBuff(byte note, bool playNote) {
  static byte buffOscNote[BUFFER] = {255};
  static byte buffOscAge[BUFFER] ={0};
  static byte OscAge = 1;
  static byte AvailOsc = NUM_OSC;
  static byte freeOsc = 0;

  // Add Note
  if (playNote == true) { 
    if(AvailOsc == 0) { 
              // AvailOsc == 0, we ran out of voices, we need to free up the oscillator that was activated first 
              // we can decrement "age" for all the resources, 
              // the oldest resource in use will thus be '0'
               Serial.println("We just ran out of available oscillators");
               for ( byte i=1; i <= NUM_OSC; i++) 
                  if (buffOscAge[i] > 0) buffOscAge[i]--;
               OscAge--;
               AvailOsc++;
               Serial.print("Total number of Oscillators Available :");Serial.println(AvailOsc);
               for (byte i = 1; i <= NUM_OSC; i++) {
                  Serial.print("=====> For OSC="); Serial.println(i);
                  Serial.print("====>buffOscAge is:"); Serial.println(buffOscAge[i]);
                  Serial.print("=====>buffOscNote is:"); Serial.println(buffOscNote[i]);
                  Serial.println("===================================================");
               }
         }
    
        //    if(AvailOsc > 0)
        // We are now allocating a resource to a new note. This means that we have to:
        // a) find the first resource available
        freeOsc = 0;
        for (byte found = 1; found <= NUM_OSC; found++) 
              if (buffOscAge[found] == 0) {
                freeOsc = found;
                // b) make sure that it is completely deactivated
                oscStop(buffOscAge[freeOsc]);       
                // c) update the relevant variables
                Serial.print("Assigning to oscillator #");
                Serial.print(freeOsc);
                Serial.print(" Age: ");
                Serial.println(OscAge);
                buffOscAge[freeOsc] = OscAge;
                buffOscNote[freeOsc] = note;
                oscPlay(note, buffOscAge[freeOsc]);
                OscAge++;
                AvailOsc--; // decrement number of available oscillators
                Serial.println("vvvvvv        NOTE ON       vvvvvvvvvv");
                Serial.print("Total number of Oscillators Available :");Serial.println(AvailOsc);
                for (byte i = 1; i <= NUM_OSC; i++) {
                   Serial.print("For OSC="); Serial.println(i);
                   Serial.print("buffOscAge is:"); Serial.println(buffOscAge[i]);
                   Serial.print("buffOscNote is:"); Serial.println(buffOscNote[i]);
                   Serial.println("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
                    }
                return;
             }
  }
  // Remove Note
  else  {   // playNote == false
          // Since we are freeing a resource, we want to:
          // a) determine which resource was used by the note
            for (byte found = 1; found <= NUM_OSC; found++) 
              if (buffOscNote[found] == note) {
                freeOsc = found;
                Serial.print("freeing up oscillator #");
                Serial.println(freeOsc);
          // b) stop that note from being played
                oscStop(buffOscAge[freeOsc]); 
                buffOscAge[freeOsc] = 0;
                buffOscNote[freeOsc] = 0;
          // c) decrement the "ages" for all the resources that were played *after* the resource that we are freeing up
                for ( byte i=1; i <= NUM_OSC; i++) {
                  Serial.print("Age for OSC#");
                  Serial.print(i);
                  if (buffOscAge[i] >= freeOsc ) buffOscAge[i]--; // latest
                  Serial.print(" == ");
                  Serial.println(buffOscAge[i]);
                  }
          // d) increment the number of available oscillators
                 OscAge--;
                 AvailOsc++;
                Serial.print("Total number of Oscillators Available After freeing the last resource:  ");
                Serial.println(AvailOsc);
                Serial.println("***********   NOTE OFF    **********************");
                Serial.print("Total number of Oscillators Available :");Serial.println(AvailOsc);
                for (byte i = 1; i <= NUM_OSC; i++) {
                   Serial.print("*For OSC="); Serial.println(i);
                   Serial.print("*buffOscAge is:"); Serial.println(buffOscAge[i]);
                   Serial.print("*buffOscNote is:"); Serial.println(buffOscNote[i]);
                   Serial.println("************************************************");
                    }
                return;
              }
        }
}

void oscPlay(byte note, byte osc) {
  
float velo = (latestVelocity * DIV127);
//pink1.amplitude(velo); //not necessary, keep it global for now, otherwise we will have to add a noise gen for each osc
   
  switch(osc){
    case(1):
   Voice1ADSR.noteOff(); // Added by AF, we need to turn the ADSR off otherwise we will hear a "click"
   Voice1OscA.frequency(noteFreqs[note]);
   Voice1OscB.frequency(noteFreqs[note + octave] * detuneFactor);
   Voice1OscA.amplitude(velo);
   Voice1OscB.amplitude(velo);
   Voice1ADSR.noteOn();
    break;
    case(2):
   Voice2ADSR.noteOff(); // Added by AF, we need to turn the ADSR off otherwise we will hear a "click"
   Voice2OscA.frequency(noteFreqs[note]);
   Voice2OscB.frequency(noteFreqs[note + octave] * detuneFactor);
   Voice2OscA.amplitude(velo);
   Voice2OscB.amplitude(velo);
   Voice2ADSR.noteOn();
    break;
    case(3):
   Voice3ADSR.noteOff(); // Added by AF, we need to turn the ADSR off otherwise we will hear a "click"
   Voice3OscA.frequency(noteFreqs[note]);
   Voice3OscB.frequency(noteFreqs[note + octave] * detuneFactor);
   Voice3OscA.amplitude(velo);
   Voice3OscB.amplitude(velo);
   Voice3ADSR.noteOn();
    break;
    case(4):
   Voice4ADSR.noteOff(); // Added by AF, we need to turn the ADSR off otherwise we will hear a "click"
   Voice4OscA.frequency(noteFreqs[note]);
   Voice4OscB.frequency(noteFreqs[note + octave] * detuneFactor);
   Voice4OscA.amplitude(velo);
   Voice4OscB.amplitude(velo);
   Voice4ADSR.noteOn();
    break;
  }
}

void oscStop(byte osc) {
//  envelope1.noteOff();
  switch(osc){
    case(1):Voice1ADSR.noteOff();
    case(2):Voice2ADSR.noteOff();
    case(3):Voice3ADSR.noteOff();
    case(4):Voice4ADSR.noteOff();
  }
}

void oscSet(){
//  waveform2.frequency(noteFreqs[globalNote + octave] * detuneFactor);
Voice1OscB.frequency(noteFreqs[latestNote + octave] * detuneFactor);
Voice2OscB.frequency(noteFreqs[latestNote + octave] * detuneFactor);
Voice3OscB.frequency(noteFreqs[latestNote + octave] * detuneFactor);
Voice4OscB.frequency(noteFreqs[latestNote + octave] * detuneFactor);
}

void myControlChange(byte channel, byte control, byte value) {
  switch (control) {
    case 100:
      //mixer1.gain(0, (value * DIV127));
      Voice1Mixer.gain(0, (value * DIV127));
      Voice2Mixer.gain(0, (value * DIV127));
      Voice3Mixer.gain(0, (value * DIV127));
      Voice4Mixer.gain(0, (value * DIV127));
      break;

    case 101:
      //mixer1.gain(1, (value * DIV127));
      Voice1Mixer.gain(1, (value * DIV127));
      Voice2Mixer.gain(1, (value * DIV127));
      Voice3Mixer.gain(1, (value * DIV127));
      Voice4Mixer.gain(1, (value * DIV127));
      break;

    case 102:
      //mixer1.gain(2, (value * DIV127));
      Voice1Mixer.gain(2, (value * DIV127));
      Voice2Mixer.gain(2, (value * DIV127));
      Voice3Mixer.gain(2, (value * DIV127));
      Voice4Mixer.gain(2, (value * DIV127));
      break;

    case 103:
      switch (value) {
        case 0:
          octave = 24;
          break;
        case 1:
          octave = 12;
          break;
        case 2:
          octave = 0;
          break;
        case 3:
          octave = -12;
          break;
        case 4:
          octave = -24;
          break;
      }
      oscSet();
      break;

    case 104:
      //envelope1.attack(3000 * (value * DIV127));
      Voice1ADSR.attack(3000 * (value * DIV127));
      Voice2ADSR.attack(3000 * (value * DIV127));
      Voice3ADSR.attack(3000 * (value * DIV127));
      Voice4ADSR.attack(3000 * (value * DIV127));
      break;

    case 105:
      //envelope1.decay(3000 * (value * DIV127));
      Voice1ADSR.decay(3000 * (value * DIV127));
      Voice2ADSR.decay(3000 * (value * DIV127));
      Voice3ADSR.decay(3000 * (value * DIV127));
      Voice4ADSR.decay(3000 * (value * DIV127));
      break;

    case 106:
      //envelope1.sustain(value * DIV127);
      Voice1ADSR.sustain(value * DIV127);
      Voice2ADSR.sustain(value * DIV127);
      Voice3ADSR.sustain(value * DIV127);
      Voice4ADSR.sustain(value * DIV127);
      break;

    case 107:
      //envelope1.release(3000 * (value * DIV127));
      Voice1ADSR.release(3000 * (value * DIV127));
      Voice2ADSR.release(3000 * (value * DIV127));
      Voice3ADSR.release(3000 * (value * DIV127));
      Voice4ADSR.release(3000 * (value * DIV127));
      break;

    case 108:
      switch (value) {
        case 0:
          Voice1OscA.begin(WAVEFORM_SINE);
          Voice2OscA.begin(WAVEFORM_SINE);
          Voice3OscA.begin(WAVEFORM_SINE);
          Voice4OscA.begin(WAVEFORM_SINE);
          break;
        case 1:
          Voice1OscA.begin(WAVEFORM_TRIANGLE);
          Voice2OscA.begin(WAVEFORM_TRIANGLE);
          Voice3OscA.begin(WAVEFORM_TRIANGLE);
          Voice4OscA.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          Voice1OscA.begin(WAVEFORM_SAWTOOTH);
          Voice2OscA.begin(WAVEFORM_SAWTOOTH);
          Voice3OscA.begin(WAVEFORM_SAWTOOTH);
          Voice4OscA.begin(WAVEFORM_SAWTOOTH);
          break;
        case 3:
          Voice1OscA.begin(WAVEFORM_PULSE);
          Voice2OscA.begin(WAVEFORM_PULSE);
          Voice3OscA.begin(WAVEFORM_PULSE);
          Voice4OscA.begin(WAVEFORM_PULSE);
          break;
      }
      break;

    case 109:
      switch (value) {
        case 0:
          Voice1OscB.begin(WAVEFORM_SINE);
          Voice2OscB.begin(WAVEFORM_SINE);
          Voice3OscB.begin(WAVEFORM_SINE);
          Voice4OscB.begin(WAVEFORM_SINE);
          break;
        case 1:
          Voice1OscB.begin(WAVEFORM_TRIANGLE);
          Voice2OscB.begin(WAVEFORM_TRIANGLE);
          Voice3OscB.begin(WAVEFORM_TRIANGLE);
          Voice4OscB.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          Voice1OscB.begin(WAVEFORM_SAWTOOTH);
          Voice2OscB.begin(WAVEFORM_SAWTOOTH);
          Voice3OscB.begin(WAVEFORM_SAWTOOTH);
          Voice4OscB.begin(WAVEFORM_SAWTOOTH);
          break;
        case 3:
          Voice1OscB.begin(WAVEFORM_PULSE);
          Voice2OscB.begin(WAVEFORM_PULSE);
          Voice3OscB.begin(WAVEFORM_PULSE);
          Voice4OscB.begin(WAVEFORM_PULSE);
          break;
      }
      break; // AF Added this on March 28th 2020
      
      case 110:
      detuneFactor = 1 - (0.05 * (value * DIV127));
      oscSet();
      break;
  

      case 111:
        //filter1.frequency(2000. * (value * DIV127) );
        Voice1LPF12db.frequency(2000. * (value * DIV127) );
        Voice2LPF12db.frequency(2000. * (value * DIV127) );
        Voice3LPF12db.frequency(2000. * (value * DIV127) );
        Voice4LPF12db.frequency(2000. * (value * DIV127) );
        break;
  
  
      case 112:
        //filter1.resonance(5.7 * (value * DIV127) ); //0.707
        Voice1LPF12db.resonance(5.7 * (value * DIV127) ); //0.707
        Voice2LPF12db.resonance(5.7 * (value * DIV127) ); //0.707
        Voice3LPF12db.resonance(5.7 * (value * DIV127) ); //0.707
        Voice4LPF12db.resonance(5.7 * (value * DIV127) ); //0.707
        break;
  
  
      case 113:
        //filter1.octaveControl( (value * DIV127) ); //3.5
        Voice1LPF12db.octaveControl( (value * DIV127) ); //3.5
        Voice2LPF12db.octaveControl( (value * DIV127) ); //3.5
        Voice3LPF12db.octaveControl( (value * DIV127) ); //3.5
        Voice4LPF12db.octaveControl( (value * DIV127) ); //3.5
        break;

        default: {
          Serial.println("Received MIDI message: ");
          Serial.print("Channel: "); Serial.println(channel);
          Serial.print("Control: "); Serial.println(control);
          Serial.print("Value: "); Serial.println(value);
        }
                
  
  }
}
