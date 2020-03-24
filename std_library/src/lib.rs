//! Simple program used to test Sunrise's libstd

use std::error::Error;
use std::ffi::CString;
use std::fs;
use std::os::raw::c_char;

fn maybe_do_the_thing() -> Result<String, Box<dyn Error>> {
    let mut iter = fs::read_dir("sdmc:/")?;
    let opt: Option<_> = iter.next();
    let res: Result<_, Box<dyn Error>> = opt.ok_or_else(|| "empty".into());
    let elem: Result<_, _> = res?;
    let entry = elem?;
    let filename = entry.path();

    Ok(filename.to_string_lossy().into_owned())
}

#[no_mangle]
pub extern "C" fn do_the_thing() -> *const c_char {
    let string = match maybe_do_the_thing() {
        Ok(s) => s,
        Err(e) => e.to_string(),
    };
    CString::new(&string as &str)
        .map(|x| x.into_raw() as *const c_char)
        .unwrap_or(b"cstring\0".as_ptr() as *const c_char)
}
