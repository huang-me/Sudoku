
output : solve.cpp transform.cpp generate.cpp
	g++ solve.cpp -o solve
	g++ transform.cpp -o transform
	g++ generate.cpp -o generate

rm : solve transform generate
	rm -f solve transform generate

style : *.cpp
	astyle --style=google --indent=spaces=4 --suffix=none *.cpp