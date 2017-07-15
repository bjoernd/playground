#[macro_use]
extern crate clap;

use clap::App;

struct Configuration {
    long_mode: bool, /* -l */
    verbose: bool, /* --verbose */
}

fn read_config() -> Configuration {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    let mut config = Configuration {
        long_mode: false,
        verbose: false,
    };

    config.long_mode = matches.is_present("long");
    config.verbose = matches.is_present("verbose");

    config
}

fn main() {
    let conf = read_config();

    println!("Long mode: {}", conf.long_mode);
}
