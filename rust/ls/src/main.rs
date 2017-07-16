#[macro_use]
extern crate log;
#[macro_use]
extern crate clap;
extern crate fern;
extern crate chrono;

use std::io;
use std::fs;
use std::path::Path;
use std::string;

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

fn configure_logging(verbose: bool) -> Result<(), fern::InitError> {
    let mut lvl = log::LogLevelFilter::Warn;
    if verbose {
        lvl = log::LogLevelFilter::Debug;
    }
    fern::Dispatch::new()
        .format(|out, message, record| {
            out.finish(format_args!(
                "{} [{}] [{:6}] {}",
                chrono::Local::now().format("%Y-%m-%d %H:%M:%S"),
                record.target(),
                record.level(),
                message
            ))
        })
        .level(lvl)
        .chain(std::io::stdout())
        .apply()?;

    Ok(())
}

fn dump_config(conf: &Configuration) {
    debug!("Long mode: {}", conf.long_mode);
}

fn iterate_path(p: &Path) -> Result<(), io::Error> {
    if p.is_dir() {
        for entry in fs::read_dir(p)? {
            let filename = entry?.file_name().into_string();
            match filename {
                Ok(f) => println!("{}", f),
                Err(f) => debug!("Failed to parse path {:?}", f),
            };
        }
    } else {
        match p.to_str() {
            Some(t) => println!("{}", t),
            None => (),
        }
    }

    Ok(())
}

fn main() {
    let conf = read_config();
    configure_logging(conf.verbose).expect("failed log initialization");

    if conf.verbose {
        dump_config(&conf);
    }

    let path = std::path::Path::new("."); // limit to cwd for now
    iterate_path(&path).expect("failed iterating path");
}
