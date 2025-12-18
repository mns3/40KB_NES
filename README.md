# 40KB_NES

![메인 타이틀 화면](nes.png)

## 🎮 프로젝트 소개
**40KB_NES**는 닌텐도 엔터테인먼트 시스템(NES/패미컴) 하드웨어 환경에서 구동되도록 제작된 게임
제한적인 8-bit 하드웨어 자원 안에서 효율을 추구하며, 게임 로직 구현하는데 중점을 둠

---
## 🛠 Tech Stack

| Category | Technology | Description |
| :--- | :--- | :--- |
| **Language** | **C (cc65), 6502 Assembly** | 로직 구현 및 하드웨어 직접 제어 (Hybrid Programming) |
| **Hardware** | **NES** | Nintendo Entertainment System (Famicom) Architecture |
| **Compiler** | **cc65** | 6502 Cross-Compiler for NES development |
| **Tools** | **Mesen, FCEUX** | Debugging (Memory Viewer, PPU Viewer 활용) |
| **Graphics** | **YY-CHR, Tiled** | Binary Tile Data Conversion & Map Editing |

---

## 🛠 기술 구현 상세 (Technical Implementation)

### 1. 8-bit 환경에 최적화된 물리 엔진 및 로직 구현 (Core Logic & Physics)
* **고정 소수점 연산 (Fixed-Point Arithmetic):**
    * 부동소수점(Float) 연산이 불가능한 NES 하드웨어(6502 CPU)에서 부드러운 가속도와 관성을 구현하기 위해 **16-bit 고정 소수점 로직**을 설계함.
    * 위치 변수(`BoxGuy.x`)의 상위 8-bit는 화면 좌표로, 하위 8-bit는 정밀한 물리 연산에 사용하여 끊김 없는 움직임을 구현.
* **C와 어셈블리 하이브리드 코딩:**
    * **cc65 컴파일러**를 활용, 복잡한 게임 로직(상태 머신 등)은 C언어로 생산성을 높이고 하드웨어 제어가 필수적인 영역은 로우레벨 코드로 최적화함.

### 2. 그래픽 파이프라인 및 메모리 최적화 (Graphics & Optimization)
* **바이너리 타일 데이터 및 VRAM 관리:**
    * 그래픽 에셋을 엔진 자동화 없이 NES PPU가 인식 가능한 **바이너리 타일 데이터**로 직접 변환하여 CHR ROM에 배치하고 관리함.
* **리소스 효율 극대화 (Mirroring & Palette Swapping):**
    * 하드웨어 스프라이트 개수 제한과 용량 한계를 극복하기 위해 **미러링(Mirroring)** 기법으로 동일 스프라이트를 반전시켜 재사용하고, **팔레트 스와핑(Palette Swapping)**을 통해 색상 정보만 교체하여 텍스처 메모리를 극한으로 절약함.
* **메타 스프라이트(Metasprite) 시스템:**
    * 8x8 사이즈의 하드웨어 스프라이트를 조합하여 하나의 캐릭터 객체로 제어하는 시스템을 구축하고, OAM(Object Attribute Memory) 버퍼를 동적으로 관리하여 깜빡임 현상을 최소화함.

### 3. 충돌 처리 및 입력 시스템 (Collision & Input System)
* **효율적인 타일 기반 충돌 처리 (AABB & Ejection):**
    * 연산 부하를 줄이기 위해 캐릭터 코너의 타일 속성을 검사하는 **AABB 방식**을 최적화 적용. 충돌 시 비트 연산을 통해 즉시 유효 좌표로 보정하는 **Ejection 알고리즘**을 구현하여 끼임 현상을 방지함.
* **Context-Sensitive Action (입력 한계 극복):**
    * A, B 두 개의 버튼만 존재하는 하드웨어적 제약을 극복하기 위해, 플레이어의 상태(지상, 공중, 벽 근처 등)에 따라 액션이 분기되는 시스템을 설계하여 조작의 깊이와 편의성을 동시에 확보함.
---

## 💡 프로젝트 회고 및 배운 점 (Retrospective)

* **Full-Cycle 개발 및 TA 역량 확보:**
    * Pixel Art 리소스 제작을 제외한 **시스템 아키텍처 설계, 물리 엔진 구현, 빌드 및 최적화**까지 개발 전 과정을 주도하며 엔지니어링 역량을 입증함.
    * 특히 아티스트의 리소스를 하드웨어 사양에 맞춰 변환(Binary Conversion)하고 배치하는 파이프라인을 구축하며 **Technical Artist로서의 가교 역할**을 수행함.

* **Low-Level 최적화 마인드셋 함양:**
    * 부동소수점 연산이 불가능한 8-bit CPU 환경에서 **고정 소수점(Fixed-point) 연산**을 고안하여 적용하고, 비트 연산(`>>`, `&`)을 활용한 **고속 충돌 처리**를 구현함.
    * 현대의 풍족한 하드웨어 환경에서는 간과하기 쉬운 **CPU 사이클 절약과 메모리 정렬(Alignment)의 중요성**을 몸소 체감하며 극한의 최적화 감각을 익힘.

* **렌더링 파이프라인의 근본적 이해:**
    * 상용 엔진(Unity/Unreal)이 자동으로 처리하던 드로우 콜(Draw Call)과 렌더링 과정을 직접 **PPU 레지스터($2000 ~ $2007) 조작**을 통해 구현함.
    * 데이터가 CPU에서 VRAM으로 이동하고, OAM을 거쳐 화면에 주사(Scanline)되기까지의 **하드웨어적 렌더링 파이프라인 전체를 깊이 있게 이해**하게 됨.

* **제약 사항을 기술로 극복하는 문제 해결 능력:**
    * 하드웨어의 물리적 한계(스프라이트 개수 제한, 버튼 부족 등)를 **미러링, 팔레트 스와핑, Context-Sensitive 입력 시스템** 등 소프트웨어적 테크닉으로 극복해내며, 주어진 환경 안에서 최상의 결과물을 만들어내는 문제 해결 능력을 기름.

---
## 👥 팀 구성 (Credits)

| 이름 | 포지션 | 담당 업무 |
|:---:|:---:|:---|
| **박민성** | **Lead Developer** | **개발 총괄 (Pixel Art 제외 전 분야)**
| **배도영** | |

---

## ⚠️ 라이선스 및 저작권 (License & Copyright)
* **Project Status:** 본 프로젝트는 기술 연구 및 개인 포트폴리오 제작을 목적으로 한 **비상업적(Non-commercial)** 프로젝트임.
* **Asset Disclaimer:**
    * 본 게임의 그래픽 리소스는 **Morphcat Games**의 **'Micro Mages'** 에셋을 활용하였음.
    * 해당 에셋의 저작권은 원작자에게 있으며, 본 프로젝트는 훌륭한 8-bit 게임인 원작의 그래픽 스타일과 최적화 방식을 학습하고 존경을 표하는 오마주(Homage)의 성격을 띠고 있음.
    * 상업적 목적으로 배포하거나 판매하지 않음.
