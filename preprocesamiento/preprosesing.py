filename = 'file1.fna'

with open(filename,'r') as file_to_read:
	with open('new_filename.fna','w') as file_to_write:
		for line in file_to_read:
			if line.startswith('>'):
				continue
			file_to_write.write(line.upper)
