
use std::io::{stdin, Write};

use rand::Rng;

const NUMBER_OF_POOR_ANIMALS: usize =20;
const NUMBER_OF_PREDATORS:usize =20;
const TIME_TO_WAIT:usize =  40000;
const ITERATIONS:usize = 15;
const SIZE_X: usize = 20;
const SIZE_Y: usize = 20;

const ENERGY_DEFAULT:u32 = 50;

// TODO: use an entity shinny thing system component stuff.
struct Animal {
    pub x: usize,
    pub y: usize,
    pub dx: u8,
    pub dy: u8,
    pub energy: u32,
}

impl Animal {
    fn new(x:usize, y:usize, dx:u8, dy:u8, energy:u32) -> Animal {
        Animal {
            x, y,dx, dy, energy
        }
    }
}

#[inline]
fn map_set(map: &mut [u8], x:usize, y:usize,val: u8) {
    
    let pos = x + SIZE_Y * y;
    assert!(map.len() > pos);
    map[x + SIZE_Y * y] = val;
}

fn main() {
    let mut map = vec![b'.'; SIZE_X * SIZE_Y];
    let mut poors_animals = Vec::with_capacity(32);
    let mut predators = Vec::with_capacity(32);
    let mut rng = rand::thread_rng();
    
    poors_animals.extend((0..NUMBER_OF_POOR_ANIMALS).map(|_| {
        let x = rng.gen_range(0..SIZE_X);
        let y = rng.gen_range(0..SIZE_Y);
        let dx = rng.gen_range(0..2);
        let dy = rng.gen_range(0..2);
        Animal::new(x, y, dx, dy, ENERGY_DEFAULT)
    }));

    predators.extend((0..NUMBER_OF_POOR_ANIMALS).map(|_| {
        let x = rng.gen_range(0..SIZE_X);
        let y = rng.gen_range(0..SIZE_Y);
        let dx = rng.gen_range(0..2);
        let dy = rng.gen_range(0..2);
        Animal::new(x, y, dx, dy, ENERGY_DEFAULT)
    }));
    
    let mut stdout = std::io::stdout();
    assert!(map.len() == SIZE_X * SIZE_Y);
    for i in 00..=ITERATIONS {
        // Reset screen
        for x in map.iter_mut() {
            *x = b'.';
        }

        // print out "to-be-eaten" animals
        for a in poors_animals.iter() {
            map_set(&mut map, a.x, a.y, b'0');
        }

        // print out "hungry" animals
        for a in predators.iter() {
            map_set(&mut map, a.x, a.y, b'@');
        }

        writeln!(stdout, "iteration: {}", i).unwrap();
        // Dump to "screen"
        for y in 00..SIZE_Y {
            let line_start = SIZE_X * y;
            let line_end = line_start + SIZE_X;
            stdout.write_all(&map[line_start..line_end]).unwrap();
            stdout.write_all(b"\n").unwrap();
        }
        stdout.flush().unwrap();

    }

}
