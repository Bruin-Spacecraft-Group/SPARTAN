# Spartan Data Packet docs

## Must implement functions

```c++
virtual int getSize() const = 0;
// example:
class IMUDataPacket : public DataPacket {
public:
    IMUDataPacket(unsigned long timestamp);
    IMUDataPacket(unsigned long timestamp, MasterDataPacket &dp);
    ~IMUDataPacket();

    virtual void populate(const MasterDataPacket &dp);

    // Size of data array
    int getSize() const;
}; // class IMUDataPacket
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
spartan::MasterDataPacket mdp;
IMUDataPacket imu_dp(/* timestamp */);

lsm6.poll(mdp);
imu_dp.populate(mdp);

std::ofstream out;
out.open(filePath);
out << imu_dp;
out.close();
```
