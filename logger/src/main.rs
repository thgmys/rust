use clap::{Arg, Command};
use log::{info, warn, error, debug, trace, LevelFilter};
use std::fs::OpenOptions;
use std::io::Write;
use env_logger::Builder;
use std::env;

fn main() {
    let matches = Command::new("CLI Logger")
        .version("1.0")
        .author("Your Name <your.email@example.com>")
        .about("Logs messages to a file")
        .arg(
            Arg::new("message")
                .short('m')
                .long("message")
                .value_name("MESSAGE")
                .about("The log message")
                .takes_value(true)
                .required(true),
        )
        .arg(
            Arg::new("level")
                .short('l')
                .long("level")
                .value_name("LEVEL")
                .about("The log level (error, warn, info, debug, trace)")
                .takes_value(true)
                .default_value("info"),
        )
        .get_matches();

    let message = matches.value_of("message").unwrap();
    let level = matches.value_of("level").unwrap();

    // Configure logging
    let mut builder = Builder::from_default_env();
    builder.format(|buf, record| {
        writeln!(buf,
            "{} [{}] - {}",
            chrono::Local::now().format("%Y-%m-%d %H:%M:%S"),
            record.level(),
            record.args()
        )
    }).filter(None, LevelFilter::Info).init();

    // Log message based on level
    match level {
        "error" => error!("{}", message),
        "warn" => warn!("{}", message),
        "info" => info!("{}", message),
        "debug" => debug!("{}", message),
        "trace" => trace!("{}", message),
        _ => info!("{}", message),
    }
}
