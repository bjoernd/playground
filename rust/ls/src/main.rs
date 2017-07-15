#[macro_use]
extern crate clap;
use clap::App;

struct Configuration {
    long_mode: bool, /* -l */
}

fn read_config() -> Configuration {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    let mut config = Configuration {
        long_mode: false,
    };

    config.long_mode = matches.is_present("long");

    config
}

fn main() {
    let conf = read_config();

    println!("Long mode: {}", conf.long_mode);
}
