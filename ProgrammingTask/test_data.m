fid = fopen('test.txt', 'rt');
C = textscan(fid, '%s','Delimiter','\t');
C2 = strsplit(C{1,1}{1,1})