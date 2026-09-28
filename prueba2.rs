fn suma(a: i32, b: i32) -> i32 {
	return a + b;
}

fn esPar(n: i32) -> bool {
	return n == 0 || n != 1 && n > 2;
}

fn saludo() -> str {
	return "hola mundo";
}

fn main() {
	let x = 10;
	let y = 20;
	let pi = 3.14;
	let letra = 'a';
	let activo = true;
	let mensaje = "hola";

	if x < y {
		let resultado = suma(x, y);
	} else {
		return;
	}

	for i in 0..10 {
		x = i;
	}

	while x < y && !activo {
		x = x + 1;
	}

	return;
}