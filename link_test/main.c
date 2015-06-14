 
 void start_motor() {
	 motor(2, -100);
 }
 
 int main() {
	 thread tid = thread_create(start_motor);
	 thread_start(tid);
	 
	 motor(1, 35);
	 motor(3, 45);
	 msleep(10000);
}
