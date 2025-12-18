# [Project Name]: 40KB_NES

![Platform](https://img.shields.io/badge/Platform-NES_(Nintendo_Entertainment_System)-red?style=flat-square)
![Tech Stack](https://img.shields.io/badge/Language-C_(cc65)_%2F_6502_ASM-blue?style=flat-square)
![Focus](https://img.shields.io/badge/Focus-Low_Level_Optimization_%26_PPU_Architecture-orange?style=flat-square)

> **"2KB RAM, 1.79MHz CPU 환경에서의 렌더링 파이프라인 구축 및 최적화 연구"**
>
> 본 프로젝트는 현대 게임 개발 환경의 추상화된 레이어를 벗어나, 8비트 하드웨어(NES)의 극한 제약 속에서 **메모리 관리, 렌더링 파이프라인 제어, 물리 연산 최적화**를 직접 구현한 기술 데모 및 게임 프로젝트입니다.

---

## 👨‍💻 Project Overview (기술적 개요)

TA(Technical Artist)로서 필수적인 **하드웨어 아키텍처 이해**와 **리소스 최적화 능력**을 배양하기 위해 진행되었습니다. NES의 PPU(Picture Processing Unit) 구조를 분석하여 제한된 스프라이트와 타일맵을 효율적으로 렌더링하고, 6502 프로세서의 사이클 한계를 고려한 로직을 구현했습니다.

---

## ⚙️ Engineering & Optimization (TA 핵심 역량)

### 1. PPU Rendering Pipeline & Graphics Optimization
NES의 그래픽 처리 장치인 PPU의 구조를 이해하고, 렌더링 병목을 해결했습니다.

* **OAM (Object Attribute Memory) Management**:
    * *Challenge*: NES는 한 스캔라인(Scanline) 당 최대 8개의 스프라이트만 렌더링 가능하며, 초과 시 깜빡임(Flickering) 현상 발생.
    * *Solution*: 매 프레임 스프라이트 우선순위를 재정렬(Sorting)하거나 순환시키는 **OAM Cycling 알고리즘**을 적용하여 시각적 결함 최소화.
* **Tilemap & Nametable Logic**:
    * 배경(Background) 렌더링을 위해 NameTable과 Attribute Table의 메모리 주소 매핑 구조를 분석하여 효율적인 맵 로딩 시스템 구축.
    * Chr-ROM(Character ROM) 내의 타일 패턴을 재사용하여 VRAM 대역폭 절약.

### 2. Memory Architecture & Performance Profiling
2KB의 시스템 RAM(Work RAM) 내에서 게임 로직을 구동하기 위해 극한의 메모리 최적화를 수행했습니다.

* **Zero Page Optimization**: 
    * 6502 프로세서의 특성상 `Zero Page ($00-$FF)` 영역의 접근 속도가 가장 빠름을 이용하여, 빈번하게 호출되는 물리 연산 변수와 플래그를 해당 영역에 배치, CPU 사이클 절감.
* **Static Allocation & Object Pooling**:
    * 동적 할당(Dynamic Allocation) 오버헤드를 없애기 위해 모든 게임 오브젝트(플레이어, 투사체 등)를 정적 배열로 선언하고, 활성/비활성 상태 플래그만 제어하는 오브젝트 풀링 기법 적용.

### 3. Physics & Collision Implementation
FPU(Floating Point Unit)가 없는 하드웨어 환경에서 부드러운 움직임을 구현했습니다.

* **Sub-pixel Precision (Fixed-Point Math)**:
    * 정수형 변수 2개를 결합하여 상위 바이트는 위치(Position), 하위 바이트는 소수점 이하(Sub-pixel)로 사용하는 **고정 소수점 연산** 체계 구축. 이를 통해 가속도 및 감속 물리 표현.
* **AABB (Axis-Aligned Bounding Box) Optimization**:
    * 충돌 체크 비용을 줄이기 위해 히트박스(Hitbox)의 오프셋을 비트 연산으로 처리하여 연산 부하 최소화.

---

## 🛠 Tech Stack

| Category | Technology | Description |
| :--- | :--- | :--- |
| **Language** | C (cc65), 6502 Assembly | 로직 구현 및 하드웨어 직접 제어 |
| **Hardware** | NES (Nintendo Entertainment System) | Target Architecture |
| **Compiler** | cc65 | 6502 Cross-Compiler |
| **Tools** | Mesen, FCEUX | Debugging (Memory Viewer, PPU Viewer 활용) |
| **Graphics** | YY-CHR, Tiled | Tile/Sprite Data Editing |

---

## 🎮 Game Design & Features

* **Genre**: 2-Player Local Competitive Platformer
* **Mechanics**:
    * 하드웨어 인터럽트(NMI)를 활용한 안정적인 60FPS 게임 루프.
    * 상태 머신(Finite State Machine) 기반의 캐릭터 애니메이션 및 로직 제어.
* **Visual Style**: 
    * 제한된 Palette(4 sub-palettes for bg, 4 for sprites)를 활용한 색상 설계.
    * *Asset Note*: 그래픽 리소스는 연구 목적으로 'Micro Mages'의 스타일과 구성을 분석하여 학습용으로 활용하였습니다.

---

## 📝 Retrospective (기술 회고)

이 프로젝트를 통해 고수준 엔진(Unreal/Unity)에서 자동화해주던 **Draw Call 처리, 메모리 정렬, 렌더링 파이프라인의 저수준 원리**를 깊이 이해하게 되었습니다.

1.  **Low-Level Understanding**: 하드웨어 레지스터에 값을 직접 쓰며 화면을 그리는 과정을 통해 셰이더와 GPU 파이프라인의 기초 원리를 체득함.
2.  **Budget Management**: TA의 핵심 역량인 '제한된 자원 내에서의 최적의 퀄리티 확보'를 8비트 환경에서의 개발을 통해 훈련함.
3.  **Problem Solving**: 문서화가 부족한 레거시 하드웨어의 동작 방식을 에뮬레이터의 디버거(Hex Viewer, PPU Viewer)를 통해 역추적하며 해결하는 디버깅 능력 향상.

---

## 🚀 Installation

1. Download `realfinalver.nes` from [Releases].
2. Run with any NES Emulator (Mesen is recommended for accuracy).

---

### Contact
* **Name**: [Your Name]
* **Role**: Aspiring Technical Artist / Game Programmer
* **Email**: [Your Email]
