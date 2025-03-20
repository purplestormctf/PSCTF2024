# purplestorm CTF 2024

#### Introduction

The AMOGESUS - CODESUS Industries, Code Security Company, which provides Secure Coding as a
Service, got compromised by the ShadowWizardMoneyGang.

The ShadowWizardMoneyGang obviously wants... money and dropped a ransom note in which they threaten
the company to leak all their internal documents and especially their SUPER SECRET KEY to all of their
infrastructure.

The company hired you to figure out which steps they took to get inside the company. 

Are you able to figure out how the compromised their servers and maybe get some "revenge"?

#### Scope

Everything on https://amogesus.com and escpecially which contains the terms `purplestorm`, `purplestormctf`, `amogesus.com` or `ShadowWizardMoneyGang`
and directly relate to the system you will encounter in the CTF is in scope.

#### Information and Rules

This is a internal and beginner friendly real-life oriented CTF which does NOT relate to any red teaming at any point. There was a historical hack on which this CTF is based on.

If you are want to discuss various steps within the team, please use the `ps-ctf-discussion` channel. If you want to avoid spoilers but ask for nudges you can go for the `ps-ctf-spoilerfree` channel.

Some parts of the CTF can require a public IP address for your callbacks. If you have your own C2 etc. feel free to use it.
If you need a jump host, you can use the credentials I send you a few days ago to access `206.189.249.170` on port 22/TCP.

If you have connection issues, use the following command:

```console
$ ssh -o PreferredAuthentications=password -o PubkeyAuthentication=no <USERNAME>@206.189.249.170
```

All of you have `sudo` privileges on the server and can install whatever you want in case you need a specific tool. Just make sure not to fuck it up ;)

Besides that I created backups of the machines and can reset them if required.

#### How long will the CTF last?

From the start at a bare minimum: two weeks. Up to a max of four weeks. After all of you folks finished the CTF and agree to make it public, we can open it up for friends and colleagues to have some fun with it. There is just no presure to finish it. Grab a coffee and have a good time.

#### Flags

Furthermore there are 10 flags to retrieve. Each for every steps the attackers took.

1. Flag: Mr. Robot
2. Flag: Dig deeper
3. Flag: Codemagic
4. Flag: Oh sint! You are in!
5. Flag: SUS!
6. Flag: We love droppin' shells
7. Flag: Heavy lifting
8. Flag: Fancy C2 generation
9. Flag: The fall of the kingdom
10. Flag: A fine addition

Example: `PS{MYDToa3FWZDUYL6B5ycvT7Rdj5DE0GSD}`

#### Flag Submission

During time and skill issues, but mainly time issues, I didn't created a fancy page with
flag submission possibilities so:

Just submit them to me via DM which the following layout:
```
PS{FLAG}
```
I will update the solved flags channel accordingly.

##### Important Note about a specific Flag...

Without spoiling to much, a very specific flag is quite finicky and even with a lot of testing it is not 100% reliable.
So if you are at a point where you think you have to "wait for a callback", for at least two or three minutes, reach out to me. Unfortunately I was not able to automate this step. Skill issue.

#### Prices

Since this is a low-budget internal CTF the prizes are just unique roles for the 1st, 2nd and 3rd place. Maybe we are doing this CTF every year from now on. Who knows...
I also was thinking about prices like subscriptions but I wanted to make this CTF as less competitive as possible. If you have useful ideas for the maybe next CTF, let me know.

#### Rules

At last I just please you to follow the rules. Read them CAREFULLY!

- Do NOT use the jump server for criminal activities at any time!
- Do not fuck around with other team member profiles or their stuff (payloads etc.). There is always this kid in the street which destroys the toys of other children and then all the other children hate this one kid. Don't be this kid.
- There is no load balancing so please operate with care.
- Cleanup behind you to avoid spoilers. This affects also the next point.
- I create very little restoring mechanics on the boxes so please use your payloads and exploits with care and restore the initial state of files. Compare this with an HTB free tier. Just stop and think for second before you fire your kernel exploit from about 15 years ago.
- NO credential brute forcing is required at any time.
- There are no rabbit holes. Everything should be in plain sight or at least have a clear next step. If you are stuck, literally enumerate more in detail.
- Please do not DoS/DDoS any part of the infrastructure.
- Passive recon instead is very welcome.
- Do not hack any gateways or routers. If you try and I find evidence for it, the whole CTF will be shutdown.
- If you find any probably unintended steps, vulnerabilities or if you think you did something wrong, reach out to me.

If you have any questions feel free to get in touch with me at any time and I try to help out.


Besides that I wish all of you a lot of fun and have a good time!
syro
