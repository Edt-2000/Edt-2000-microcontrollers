use std::{async_iter::FromIter, net::UdpSocket};

fn main() {
    let listener = UdpSocket::bind("127.0.0.1:12346").expect("This should be good");

    println!("HI");

    loop {
        let mut buffer: Vec<u8> = vec![0; 100];

        let (received, port) = listener.recv_from(&mut buffer).expect("Bork");

        let message = OscMessage::new(buffer);

        let message_data: FromIter<i32> = message
            .data
            .iter()
            .map(|datum: &OscData| datum.read_int())
            .collect();

        println!(
            "received {received} bytes from {port} for {} with {} items, data {:?}",
            message.address,
            message.data.len(),
            message_data
        );
    }
}

struct OscMessage {
    address: String,
    data: Vec<OscData>,
}

union DataUnion {
    int: i32,
    float: f32,
}

struct OscData {
    data_type: u8,
    data: DataUnion,
}

impl OscData {
    fn read_int(&self) -> Option<i32> {
        if self.data_type == b'i' {
            return Some(unsafe { self.data.int });
        }

        return None;
    }

    fn read_float(&self) -> Option<f32> {
        if self.data_type == b'f' {
            return Some(unsafe { self.data.float });
        }

        return None;
    }
}

impl OscMessage {
    fn new(buffer: Vec<u8>) -> OscMessage {
        let address_length = buffer.iter().position(|&x| x == b'\0').expect("YOLO");
        let data_length = buffer
            .iter()
            .skip(address_length + 2)
            .position(|&x| x == b'\0')
            .expect("YOLO");

        let address = buffer[..address_length].to_vec();
        let address = String::from_utf8(address).unwrap();

        let data_types = buffer[(address_length + 2)..(address_length + 2 + data_length)].to_vec();

        let data_start = address_length + 2 + data_length;
        let data_start = (4 - (data_start % 4)) + data_start;

        let mut data: Vec<OscData> = Vec::new();

        for (index, datum) in data_types.iter().enumerate() {
            let mut raw_data = [0u8; 4];
            for i in 0..4 {
                raw_data[i] = buffer[data_start + i + (index * 4)];
            }

            let union = match datum {
                b'i' => DataUnion {
                    int: i32::from_be_bytes(raw_data),
                },
                b'f' => DataUnion {
                    float: f32::from_be_bytes(raw_data),
                },
                // not supported
                _ => continue,
            };

            data.push(OscData {
                data_type: *datum,
                data: union,
            });
        }

        OscMessage { address, data }
    }
}
