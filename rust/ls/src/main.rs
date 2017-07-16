#[macro_use]
extern crate log;
#[macro_use]
extern crate clap;
extern crate fern;
extern crate chrono;

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

fn main() {
    let conf = read_config();
    configure_logging(conf.verbose).expect("failed log initialization");

    if conf.verbose {
        dump_config(&conf);
    }
}
