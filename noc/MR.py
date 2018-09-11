import math
import matplotlib.pyplot as plt
import numpy as np

k_e = 1     # the fraction of optical power couple into
k_d = 1     # the fraction of optical power couple out
k_p = 1     # intinstic power loss per round-trip in the MR

L_VCSEL_0 = 1550  # lambda_vcsel_0
L_MR_0    = 1550  # lambda_mr_0

T_0         = 25     # normal temperture
row_vcsel   = 0.09
alpha       = 2.4
belta       = 0.00075
T_th        = 40
epsilon     = 0.403
garma       = 0.00217
L_MR_resonance_peak     = 0.5
row_MR                  = 0.06
fabrication_sigma       = 0.4
P_MR_ON                 = 0.02
Modulation_speed        = 10
S_RX                    = -14.2
L_propagate             = 0.17
L_crossing              = 0.12
link_length             = 20
crossing_number         = 10
E_serializer            = 0.16
E_driver                = 0.1125
E_PD                    = 0.0003
E_deserializer          = 0.128
E_TIA_LA                = 0.3375
U_slope                 = 0.0729
U_th                    = 1.0135
P_thermaltuning         = 3.5
Lambda                  = 1550
elec_switch_off_on      = 0.4
thermal_switch_off_on   = -0.4
modulation_0_1          = 0.4
lambda_misplace_factor  = 3
P_modulator_data_0      = 0


k_e                     = 6.59  # kapler loss in
k_d                     = 6.59  # kapler loss output
k_p                     = 1     # kapler loss in circle

delta   = 0.62  # delta in 3-db bandwidth
T_MR_0      = 25
T_VCSEL_0   = T_0

def GetVCSELTh(T):
    return (alpha + belta*math.pow(T - T_0, 2))


def GetLambdaMR(T):
    return (L_MR_0 + row_MR*(T - T_MR_0))

def GetLambdaVCSEL(T):
    return (L_VCSEL_0 + row_vcsel*(T - T_VCSEL_0))


def GetDropPower(L_VCSEL, L_MR):
    num     = 2 * k_e * k_d
    divide  = math.pow(k_e, 2) + math.pow(k_d, 2) + math.pow(k_p, 2)
    k       = math.pow( num / divide, 2)
    return k * math.pow(delta, 2) / (math.pow((L_VCSEL - L_MR), 2) + math.pow(delta, 2))


def GetThroughPower(L_VCSEL, L_MR):
    num     = 4*math.pow(k_e, 2)*(math.pow(k_d, 2) + math.pow(k_p, 2))
    divide  = math.pow(math.pow(k_e, 2) + math.pow(k_d, 2) + math.pow(k_p, 2), 2)
    k       = num / divide
    return 1 - k*(math.pow(delta, 2) / (math.pow((L_VCSEL - L_MR- 1), 2) + math.pow(delta, 2)))


def PowerToDb(transfer):
    return 10*math.log10(transfer)


# off chip
L = np.arange(1545, 1555, 0.1)
T = np.arange(0, 100, 1)
DropPower       = []
ThoughtPower    = []
# for T_i in T:
#     DropPower.append(GetDropPower(1550, GetLambdaMR(T_i)))
#
# for T_i in T:
#     ThoughtPower.append(GetThroughPower(1550, GetLambdaMR(T_i)))

for L_i in L :
    DropPower.append(PowerToDb(GetDropPower(L_i, GetLambdaMR(25))))

for L_i in L :
    ThoughtPower.append(PowerToDb(GetThroughPower(L_i, GetLambdaMR(25))))

plt.plot(L, DropPower, "r--", L, ThoughtPower)
plt.ylabel("drop power")
plt.show()

