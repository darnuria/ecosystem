use std::io::Write;

use rand::Rng;

const NUMBER_OF_POOR_ANIMALS: usize = 20;
const NUMBER_OF_PREDATORS: usize = 20;
// /const TIME_TO_WAIT: usize = 40000;
const ITERATIONS: usize = 15;
const SIZE_X: usize = 20;
const SIZE_Y: usize = 20;
const PROBABILITY_MOVE: u32 = 100;
const ENERGY_DEFAULT: i32 = 50;
const ENERGY_DEFAULT_SPENT_HERBIVOROUS: i32 = 1;
const REPRODUCTION_RATE_HERBIVOROUS: u32 = 9;

// TODO: use an entity shinny thing system component stuff.
#[derive(Debug)]
struct Animal {
    pub x: usize,
    pub y: usize,
    pub dx: i8,
    pub dy: i8,
    pub energy: i32,
}

#[inline]
fn toric_coordinate(x: usize, direction: i8, size: usize) -> usize {
    let size = size as isize;
    let x = x as isize;
    let dir = direction as isize;
    let r = (x + dir + size) % size;
    r as usize
}

/// A maybe too much object oriented abstraction.
/// In this first version I wanted to stay close to the C code.
/// May change.
impl Animal {
    fn new(x: usize, y: usize, dx: i8, dy: i8, energy: i32) -> Animal {
        Animal {
            x,
            y,
            dx,
            dy,
            energy,
        }
    }

    fn update_position<R: Rng + ?Sized>(&mut self, dice: &mut R) {
        self.x = toric_coordinate(self.x, self.dx, SIZE_X);
        self.y = toric_coordinate(self.y, self.dy, SIZE_Y);
        if PROBABILITY_MOVE > dice.gen_range(0..=100) {
            // is this -1 neccessary?!
            self.dx = dice.gen_range(-1..=1);
            self.dy = dice.gen_range(-1..=1);
        }
    }

    fn update_energy(&mut self, energy_spent: i32) {
        self.energy -= energy_spent
    }

    fn is_dead(&self) -> bool {
        self.energy <= 0
    }
}

#[inline]
fn map_set(map: &mut [u8], x: usize, y: usize, val: u8) {
    let pos = x + SIZE_Y * y;
    assert!(map.len() > pos);
    map[pos] = val;
}

fn update_herbivous<R: Rng + ?Sized>(mut animals: Vec<Animal>, dice: &mut R) -> Vec<Animal> {
    // update
    for a in animals.iter_mut() {
        a.update_position(dice);
        a.update_energy(ENERGY_DEFAULT_SPENT_HERBIVOROUS);
    }
    animals.retain(|a| !a.is_dead());
    let new_animals = animals
        .iter()
        .map(|a| (a.x, a.y))
        .filter_map(|(x, y)| {
            if REPRODUCTION_RATE_HERBIVOROUS > dice.gen_range(0..1000) {
                let dx = dice.gen_range(0..2);
                let dy = dice.gen_range(0..2);
                Some(Animal::new(x, y, dx, dy, ENERGY_DEFAULT))
            } else {
                None
            }
        })
        .collect::<Vec<_>>();
    animals.extend(new_animals);
    animals
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

    predators.extend((0..NUMBER_OF_PREDATORS).map(|_| {
        let x = rng.gen_range(0..SIZE_X);
        let y = rng.gen_range(0..SIZE_Y);
        let dx = rng.gen_range(0..2);
        let dy = rng.gen_range(0..2);
        Animal::new(x, y, dx, dy, ENERGY_DEFAULT)
    }));

    let stdout = std::io::stdout();
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
        {
            let mut stdout = stdout.lock();
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

        // GAME UPDATE
        poors_animals = update_herbivous(poors_animals, &mut rng);
    }
}
