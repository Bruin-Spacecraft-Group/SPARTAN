# Spartan Data Packet docs

*Note: PacketType has been renamed to DataPacket, while MasterDataPacket has been tentatively deprecated.*

## Must implement functions

```c++
virtual int getSize() const = 0;
// example:
class IMUDataPacket : public DataPacket {
public:
    // Size of data array
    int getSize() const {
        return 7;
    }
    // virtual void populate(const MasterDataPacket &dp);

    IMUDataPacket(unsigned long timestamp, float * data): DataPacket(timestamp, data) {}
};
```

## Format of serialization

output stream format
```
timestamp
datapacket size
data[0]
data[1]
...
data[size-1]
```

input stream is exactly the same.

Example input and output
```c++
DataPacket * dp;
lsm6.poll(dp);
std::ofstream out;
out.open(filePath);
out << * dp;
out.close();
```