fn promedio(a: f64, b: f64) -> f64 {
	return (a + b) * 0.5;
}

fn esPar(n: i32) -> bool {
	return n == 0 || n != 1 && n > 2;
}

fn saludo() -> str {
	return "hola mundo";
}

fn main() {
	let contador = 0;
	let limite = 10;
	let pi = 3.14;
	let letra = 'a';
	let activo = true;
	let mensaje = "hola";
	while contador < limite && !activo {
		contador = contador + 1;
	}
	if contador >= limite || letra == 'b' {
		let r = promedio(pi, 2.0 * pi);
	} else {
		let r = saludo();
	}
	for i in 0..limite {
		let sq = esPar(i * i + 1);
	}
	for j in contador..limite * 2 {
		contador = contador * j;
	}
	return;
}
