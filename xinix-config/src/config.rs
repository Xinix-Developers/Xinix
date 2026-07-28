use target_tuples::pieces::Architecture;

#[derive(Copy, Clone, Debug, Hash, PartialEq, Eq, Default)]
pub enum Bootloader {
    #[default]
    Limine,
}

#[derive(Copy, Clone, Debug, Hash, PartialEq, Eq)]
pub struct ConfigInfo {
    pub arch: Architecture,
    pub bootloader: Bootloader,
}

impl Default for ConfigInfo {
    fn default() -> Self {
        ConfigInfo { arch: Architecture::parse(std::env::consts::ARCH), bootloader: Bootloader::Limine }
    }
}