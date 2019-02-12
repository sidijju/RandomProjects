# -*- coding: utf-8 -*-

"""
To run on a Mac:
    1. Install Homebrew and pip (if not already present)
    2. brew install portaudio
    3. pip install pyaudio
"""

import pyaudio
import wave
import sys
import scipy.io.wavfile
from IPython.display import Audio
import numpy as np

def normalize(arr):
    min_val = np.amin(arr)
    max_val = np.amax(arr)
    arr = arr - min_val
    arr = np.divide(arr, (max_val - min_val))
    return arr

def play_wav(wav_filename, chunk_size=1024):
    print("* playing file")
    p = pyaudio.PyAudio()
    # Open stream.
    wf = wave.open(wav_filename, 'rb')
    stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
        channels=wf.getnchannels(),
        rate=wf.getframerate(),
                    output=True)

    data = wf.readframes(chunk_size)
    while len(data) > 0:
        stream.write(data)
        data = wf.readframes(chunk_size)

    # Stop stream.
    stream.stop_stream()
    stream.close()

    # Close PyAudio.
    p.terminate()
    print("* finished playing")

if __name__ == "__main__":
    CHUNK = 1024
    FORMAT = pyaudio.paFloat32
    CHANNELS = 2
    RATE = 44100
    RECORD_SECONDS = 3
    WAVE_OUTPUT_FILENAME = "Despacito-2.wav"

    p = pyaudio.PyAudio()
    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK)

    #RECORDING AUDIO
    print("* recording")

    decoded = []
    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        decoded.append(np.fromstring(data, 'Float32'))

    decoded = np.nan_to_num(np.array(decoded, dtype = "float32"))

    print("* done recording")

    stream.stop_stream()
    stream.close()
    p.terminate()

    #PROCESS TO CHECK SIMILARITY
    np.savetxt("alexa.txt", decoded, delimiter=',')
    alexa_array = np.genfromtxt("alexa.txt", dtype=None, delimiter = ',')

    decoded = normalize(decoded)
    alexa_array = normalize(np.nan_to_num(alexa_array))

    total_diff = 0

    for i in range(len(decoded)):
        for j in range(len(alexa_array[i])):
            total_diff += abs(alexa_array[i][j] - decoded[i][j])

    total_diff = total_diff / ((len(decoded) * len(decoded[i])))
    total_diff = total_diff * 10000000000

    print("* SIMILARITY INDEX DETERMINATOR (otherwise known as SID): " + str(total_diff))
    if(100 < total_diff < 125):
        print("* SID IN RANGE - BRACE FOR THE MEMES!")
        play_wav(WAVE_OUTPUT_FILENAME, chunk_size = CHUNK)
