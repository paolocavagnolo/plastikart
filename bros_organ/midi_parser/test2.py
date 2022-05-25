from mido import MidiFile

mid = MidiFile('organv7.mid', clip=True)


print(mid.tracks)

t = mid.tracks[1]



aOn = []
aOff = []
bOn = []
bOff = []
cOn = []
cOff = []

dOn = []
dOff = []
eOn = []
eOff = []
fOn = []
fOff = []

gOn = []
gOff = []
hOn = []
hOff = []
iOn = []
iOff = []

gt = 0

for m in t:
	gt = gt + m.time

	if 'note' in m.type:
		if m.note == 30:
			if m.type == 'note_on':
				aOn.append(int(gt/960*1000))
			else:
				aOff.append(int(gt/960*1000))
		elif m.note == 31:
			if m.type == 'note_on':
				bOn.append(int(gt/960*1000))
			else:
				bOff.append(int(gt/960*1000))
		elif m.note == 32:
			if m.type == 'note_on':
				cOn.append(int(gt/960*1000))
			else:
				cOff.append(int(gt/960*1000))

		elif m.note == 39:
			if m.type == 'note_on':
				dOn.append(int(gt/960*1000))
			else:
				dOff.append(int(gt/960*1000))
		elif m.note == 40:
			if m.type == 'note_on':
				eOn.append(int(gt/960*1000))
			else:
				eOff.append(int(gt/960*1000))
		elif m.note == 41:
			if m.type == 'note_on':
				fOn.append(int(gt/960*1000))
			else:
				fOff.append(int(gt/960*1000))

		elif m.note == 48:
			if m.type == 'note_on':
				gOn.append(int(gt/960*1000))
			else:
				gOff.append(int(gt/960*1000))
		elif m.note == 49:
			if m.type == 'note_on':
				hOn.append(int(gt/960*1000))
			else:
				hOff.append(int(gt/960*1000))
		elif m.note == 50:
			if m.type == 'note_on':
				iOn.append(int(gt/960*1000))
			else:
				iOff.append(int(gt/960*1000))

	


print("unsigned long aOn[] = ",end='')
print(aOn)
print("unsigned long aOff[] = ",end='')
print(aOff)

print("unsigned long bOn[] = ",end='')
print(bOn)
print("unsigned long bOff[] = ",end='')
print(bOff)

print("unsigned long cOn[] = ",end='')
print(cOn)
print("unsigned long cOff[] = ",end='')
print(cOff)

print("unsigned long dOn[] = ",end='')
print(dOn)
print("unsigned long dOff[] = ",end='')
print(dOff)

print("unsigned long eOn[] = ",end='')
print(eOn)
print("unsigned long eOff[] = ",end='')
print(eOff)

print("unsigned long fOn[] = ",end='')
print(fOn)
print("unsigned long fOff[] = ",end='')
print(fOff)

print("unsigned long gOn[] = ",end='')
print(gOn)
print("unsigned long gOff[] = ",end='')
print(gOff)

print("unsigned long hOn[] = ",end='')
print(hOn)
print("unsigned long hOff[] = ",end='')
print(hOff)

print("unsigned long iOn[] = ",end='')
print(iOn)
print("unsigned long iOff[] = ",end='')
print(iOff)

print("int i_aLen = ",end='')
print(len(aOn))
print("int i_bLen = ",end='')
print(len(bOn))
print("int i_cLen = ",end='')
print(len(cOn))
print("int i_dLen = ",end='')
print(len(dOn))
print("int i_eLen = ",end='')
print(len(eOn))
print("int i_fLen = ",end='')
print(len(fOn))
print("int i_gLen = ",end='')
print(len(gOn))
print("int i_hLen = ",end='')
print(len(hOn))
print("int i_iLen = ",end='')
print(len(iOn))

