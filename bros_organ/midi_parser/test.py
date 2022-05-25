from MIDI import MIDIFile

c=MIDIFile('track5.mid')
c.parse()

print("\n")
print("GENERAL INFO")
print("-"*12)
print()
print(str(c))
print("\n"*2)

print("TRACKS  INFO")
print("-"*12)
print()

seq1 = []

tpqn = 960
bpm = 120

for idx, track in enumerate(c):
	track.parse()
	print(f'Track {idx}:')

	if idx == 1 or idx == 2:
		for e in track:
			print(e)
			if 'tempo' in dir(e):
				print("TEMPO: " + str(e.tempo))
			else:

				print(e.time/tpqn/bpm*60,end='')
				print('\t',end='')

				if 'channel' in dir(e):
					print(str(e.channel),end='')
				else:
					print("   ",end='')
				print('\t',end='')

				if 'command' in dir(e):
					print(str(e.command),end='')
				else:
					print("   ",end='')
				print('\t',end='')

				if 'message' in dir(e):
					print(str(e.message),end='')
				else:
					print("   ",end='')
				print('\t',end='')
				print()
	else:
		print("not displaying")
		print()