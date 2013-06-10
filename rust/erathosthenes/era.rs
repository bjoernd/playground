fn eratosthenes(max : uint) -> ~[bool]
{
	let mut prime: ~[bool] = vec::from_elem(max, true);
	let mut i = 2;

	while (i < max) {
		let mut idx = i * i;
		while (idx < max) {
			if (prime[idx]) {
				prime[idx] = false;
			}
			idx += i;
		}
		i += 1;
	}

	return prime;
}

fn main()
{
	enum vals {
		MAX_NUM = 256,
	};
	
	println("Sieve of Erathosthenes");

	let prime = eratosthenes(MAX_NUM as uint);
	let mut i = 0;

	while (i < MAX_NUM as uint) {
		if (prime[i]) {
			print(fmt!("%? ", i));
		}
		i += 1;
	}
	println("");
}
