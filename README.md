# 🌀 AurixTc275DCmotorPIDcon

본 프로젝트는 **Infineon AURIX TC275 Evaluation Board**를 기반으로, **DC 모터를 PID 제어(PID Control)**하는 임베디드 제어 시스템 구현 예제입니다. AURIX의 다양한 주변 모듈(CCU6, GPT12, ERU, ADC, GPIO, UART 등)을 활용하여 실시간 모터 속도 제어, 외부 인터럽트 기반 센서 이벤트 처리, PWM 생성 및 피드백 기반의 정밀한 PID 제어를 수행합니다.

---

## 📌 프로젝트 목적

- **DC 모터에 대한 PID 제어**를 구현
- AURIX TC275의 **CCU6 모듈을 통한 PWM 신호 생성**
- **GPT12 타이머**를 이용한 정밀한 시간 제어
- **ERU 인터럽트**를 이용한 센서 이벤트 감지 및 제어 흐름 동기화
- **ADC를 통해 센서 값 피드백 수집**
- **UART 출력으로 실시간 상태 모니터링**

---

## ⚙️ 사용된 주요 모듈 및 역할

| 모듈 | 설명 | 활용 목적 |
|------|------|-----------|
| **CCU6** (Capture/Compare Unit 6) | 고정밀 PWM 출력 | DC 모터 구동용 PWM 신호 생성 |
| **GPT12** (General Purpose Timer) | 정밀 타이머 | 주기적 PID 제어 실행 및 시간 기준 생성 |
| **ERU** (External Request Unit) | 외부 인터럽트 감지 | 센서 트리거 또는 외부 이벤트 발생 시 인터럽트 실행 |
| **ADC** (Analog-to-Digital Converter) | 센서 입력 | 아날로그 센서로부터 속도/위치 데이터를 수집하여 PID에 입력 |
| **GPIO** | 디지털 제어 | 모터 드라이버의 Enable 핀 제어 |
| **UART (ASCLIN)** | 직렬 통신 | 디버깅/로깅/튜닝 값 확인용 시리얼 출력 |

---

## 🧩 시스템 구성도
[AURIX TC275 Board]
├── CCU6 PWM Output ──> Motor Driver (IN 핀)
├── GPIO Output ──────> Motor Driver (EN 핀)
├── ADC Input <─────── Sensor (속도 / 위치)
├── ERU Interrupt <─── External Trigger (예: Encoder A/B)
├── GPT12 Timer ───────> 주기적 PID 실행
└── UART (Optional) ──> PC 디버깅용 시리얼 출력
---

## 🧠 PID 제어 개요

PID (Proportional-Integral-Derivative) 제어는 시스템 오차를 최소화하여 목표 속도 또는 위치에 도달하도록 조정합니다.

**제어 공식:**
u(t) = Kp * e(t) + Ki * ∫e(t)dt + Kd * de(t)/dt
- `e(t)`: 목표값과 현재 센서값의 차이
- `u(t)`: 제어 출력 (PWM 듀티비)
- `Kp`, `Ki`, `Kd`: 제어 파라미터

---

## 🛠️ 개발 환경

| 항목 | 설명 |
|------|------|
| MCU | Infineon AURIX TC275 |
| IDE | AURIX Development Studio / TASKING VX-toolset |
| 디버깅 | TRACE32 / On-board Debugger |
| OS | Windows 10/11 |
| 보조 장치 | DC 모터, 센서, 드라이버, UART 케이블 등 |

---

## 📁 폴더 구조
AurixTc275DCmotorPIDcon/
│
├── 0_Src/
│   ├── AppSw/
│   │   └── Tricore/
│   │       ├── Main.c         # 메인 루프 및 초기화
│   │       ├── PID.c / PID.h  # PID 제어 알고리즘
│   │       ├── MotorCtrl.c    # PWM 및 GPIO 제어
│   │       ├── Timer.c        # GPT12 타이머 설정 및 ISR
│   │       └── ERU_Handler.c  # 외부 인터럽트 처리
│   └── BaseSw/                # iLLD 기반 주변장치 제어
│
├── .project                   # AURIX 프로젝트 메타 정보
└── README.md                  # 본 설명서
---

## ▶️ 실행 방법

1. **프로젝트 불러오기**: AURIX Development Studio 또는 TASKING IDE에서 프로젝트 로드  
2. **핀 연결 확인**: PWM, ADC, EN, 외부 인터럽트 입력, UART 핀 확인  
3. **빌드 및 업로드**: 보드에 바이너리 업로드  
4. **테스트 시작**: 모터 구동 및 PID 튜닝 확인  
5. (선택) **Tera Term 등으로 UART 출력 확인**  

---

## 📈 향후 개선 계획 (TODO)

- [ ] UART를 통한 실시간 PID 파라미터 조정 기능  
- [ ] ADC 필터링 적용 (Low-pass Filter 등)  
- [ ] Dead-time 제어 추가 (모터 보호 목적)  
- [ ] PI/PD 모드 선택 옵션 제공  
- [ ] EEPROM을 이용한 파라미터 저장 기능  

---

## 📚 참고 자료

- [Infineon AURIX TC275 Product Page](https://www.infineon.com/cms/en/product/microcontroller/32-bit-tricore-microcontroller/aurix-tc275/)
- [Infineon iLLD Documentation](https://www.infineon.com/cms/en/tools/aurix-development-studio/)
- [Application Note: Using ERU and CCU6 in Motor Control](https://www.infineon.com/)
- [Motor Control Application Notes (Infineon)](https://www.infineon.com/cms/en/applications/industrial/motor-control/)

---

## 🙋‍♂️ 개발자

> **Junhwi Park**  
> Embedded Developer, AURIX TC275 기반 실시간 제어 관심  
> GitHub: [@Junhwipark](https://github.com/Junhwipark)

---

## 📝 라이선스

이 프로젝트는 [MIT License](LICENSE)를 따릅니다.
