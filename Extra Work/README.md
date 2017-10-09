# Lab 3: Extra Work: Engery Trace

I compared the amount of energy used between polling and interrupts on the MSP430FR6989.
The picture shows an over 70% delta between the two with polling being more effecient. This came as a suprise to me, because I thought for sure interrupts would have been more efficient. This could have been an issue with the way I coded each of the files. For interrupts, had I taken advantage of low power mode I believe it would have been more efficient than polling.