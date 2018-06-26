void main(void)
{
	int a;
	int b;
	int x;

	a = 1;				/* a = 1 */
	b = 2 + a;			/* b = 3 */
	output(0, a);
	output(1, b);

	a = a * b;			/* a = 3 */
	b = (b / a) + 1;	/* b = 2 */

	output(0, a);
	output(1, b);
	x = input();

	output(2, x);

	if(a > b){
		a = a + b;			/* a = 5 */
	}
	if(b == 2) b = x;		/* b = x */

	output(0, a);
	output(1, b);

	while(a < 10){
		a = a + 1;
		output(2, a);
	}

	output(0, 5);
	output(1, 5);
	output(2, 5);

	return;
}