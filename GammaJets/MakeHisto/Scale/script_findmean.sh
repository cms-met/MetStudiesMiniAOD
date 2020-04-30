cp findmean.C test.C

for i in 50 60 80 90 100 110 130 150 175 200 225 250 275 305 335 365 400 440 500; do

sed 's/upara50/'upara${i}'/g' < test.C > test1.C

root -l -b -q test1.C

rm -f test1.C

done

rm -f test.C 

root -l -q make_response_histo.C
