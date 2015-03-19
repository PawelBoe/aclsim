A small C-program for simulating cisco ACL filtering functions by applying rules to a fixed test-vector file.

This is still in progress and therefore not yet safe to use. A first working prototype is usable, but beware that it contains bugs. It may produce errors if you don´t stick to the correct rule and vector syntax.
Installation:
- "git clone https://github.com/PawelBoe/aclsim.git" into a directory of your choice
- run "make" to generate the bin/ and obj/ folder.
- go to bin/ and use ./aclsim according to your needs..

The usage of this program is as follows: ./aclsim ruleFile  vectorFile

Rule syntax: action protocol sourceIp (operation port(s)) destinationIp (operation port(s))

Vector syntax: protocol sourceIp sourcePort destinationIp destinationPort (flags)

- Actions: permit, deny, remark
- Protocols: ip, tcp, udp, icmp, esp
- Port operations: eq, neq, gt, lt, range
- IP address operations: any, host, (wildcard format)


I´m just learning C, meaning that at this stage the program probably contains some bad programming, consider yourself warned..
