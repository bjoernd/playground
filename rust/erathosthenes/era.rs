fn eratosthenes(max : uint) -> ~[bool]
{
	let mut prime: ~[bool] = vec::from_elem(max, true);

	for uint::range(2u, max) |i| {
		for uint::range_step(i*i, max, i as int) |idx| {
			prime[idx] = false;
		}
	}

	prime
}

fn main()
{
	enum vals {
		MAX_NUM = 256,
	};
	
	println("Sieve of Erathosthenes");

	let prime = eratosthenes(MAX_NUM as uint);

	for uint::range(0, MAX_NUM as uint) |i| {
		if (prime[i]) {
			print(fmt!("%? ", i));
		}
	}

	println("");
}
