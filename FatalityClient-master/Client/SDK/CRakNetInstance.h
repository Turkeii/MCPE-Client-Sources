#pragma once

class C_RakNetInstance {
	char pad_0000[0x3C8];  //0x0008
public:
	TextHolder numericalIp;  //0x03D0
	TextHolder serverIp;        //0x03F0
	uint32_t serverPort;   //0x0400

private:
	virtual ~C_RakNetInstance();
	virtual __int64 onAppResumed(void);
	virtual __int64 onAppSuspended(void);

public:
	virtual TextHolder* getLocalIps(TextHolder*);
	virtual TextHolder* getLocalIp(TextHolder*);

public:
	virtual unsigned int getPort(void) const;

public:
	virtual __int64 getRefinedLocalIps(void) const;
	virtual __int64 getConnectedGameInfo(void) const;

public:
	virtual void setupNatPunch(bool);

public:
	virtual __int64 getNatPunchInfo(void) const;
	virtual __int64 startNatPunchingClient(__int64);
	virtual __int64 addConnectionStateListener(__int64);
	virtual __int64 removeConnectionStateListener(__int64);

public:
	virtual bool isIPv4Supported(void) const;
	virtual bool isIPv6Supported(void) const;

public:
	virtual __int64 getIPv4Port(void) const;
	virtual __int64 getIPv6Port(void) const;
	virtual __int64 getGUID(void) const;
	virtual void connect(void*);
	virtual void disconnect(void);
	virtual int getTransportIdentifier(void);

public:
	bool isonaServer() { return !(serverIp.textLength == 0); }

};                         //Size: 0x0848
