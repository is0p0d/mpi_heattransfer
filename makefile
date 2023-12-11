# 2023 Jim M
plot: heat
	./heat 100 300 1 output.dat && python3 plot.py output.dat

heat: driver.c
	gcc driver.c -o heat

clean:
	rm heat
	rm *.o
	rm *.dat