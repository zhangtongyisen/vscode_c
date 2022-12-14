软件测试基础
===

什么是软件
---
软件不仅仅包含其应用程序本身，还包括与其匹配的程序文档（使用说明书），以及软件所包含的必须的操作数据。

软件评估指标
---

什么是软件测试
---
**狭义**上：利用一定的方法对软件的质量或者使用性进行判断和评估的过程。
**广义**上：使用人工或自动的手段来运行或测量软件系统的过程，以检验软件是否满足规定的要求，并找出与预期结果之间的差异。

软件测试的任务
---
**找出、定位、修改**。修改后要做**回归测试**，对已修改的部分进行再次的测试，避免引入新错误。
**方向**：
+ 找错误，反向思维
+ 证明正常工作，正向思维
+ 目前方法的出发点一般是找错误，因为没法证明软件是正确的

**什么时候停止测试**：
+ 继续测试没有产生新的失效
+ 继续测试没有发现新的缺陷
+ 回报很小
+ 已经达到要求的覆盖
+ 无法考虑新的测试用例（若已遵循测试规则和指导方针，则可选）

测试用例
---
定义：测试用例是为特定的目的而设计的一组测试输入、执行条件和预期的结果。测试用例实质性的最小实体。简单的说，测试用例就是设计一个场景，使软件程序在这种场景下，必须能够正常运行并且达到程序所涉及的执行结果
组成部分：**包含用例ID、用例名称、测试目的、测试环境、前提条件、测试步骤、预期结果。其他信息。**

测试过程模型
---
-  瀑布模型：计划、需求、设计、编码、测试、运维。执行过程为前面一个阶段执行完之后，再进入下一个阶段。重要文档：需求规格说明书，概要设计，详细设计。

-  螺旋模型：渐进式的开发模式。强调的是 “风险”. 每一个环里面都有风险分析这一阶段, 每一环的工作都比前一环要多, 是为了减少项目风险
  适合的项目: 复杂度高, 风险大, 规模庞大。

-  敏捷开发模型：故事（需求）、迭代（一个版本的开发周期）、燃尽（进度）、站立会议。   每个版本都可以演示，每个版本的迭代周期短

-  V模型，W模型，双V模型
  <image src="./V模型.png"></image>
  <image src="./W模型.png"></image>
  <image src="./双V.png"></image>

软件测试原则
---
+ 所有的测试都应追溯到用户的需求
+ 尽早的和不断地进行软件测试（缺陷放大原则，测试成本随时间的推移而增加）
+ 8-2原则
  1. 测试程序发现的错误80%来源于程序的20%
  2. 提前测试可发现80%的错误，系统测试找出剩下bug的16%的80%，最后的4%可能要等用户爆发式增长起来才可能暴露
  3. 80%的工程用在20%的需求上（及关键需求）
+ 避免自己测自己的程序
+ 回归测试中避免引入新的错误。

软件测试流程
---
制定测试计划、测试设计、测试开发、测试执行、评估测试。
本地化测试
国际化测试

软件测试的分类
---
- **黑盒测试**：对软件内部如何实现不了解，以外部的视角来视察软件。**黑盒测试方法**：等价类边界值，因果图，判定表，错误推测法
    -  **等价类划分法和边界值分析：**
        - 如何划分有效和无效等价类：
            1. 如果一个变量在某一个范围内，给他一个有效等价类两个无效的等价类
            2. 如果一个变量取值在某一个集合范围内，可以在集合内取一个有效等价类，再集合外取一个无效等价类
            3. 如果一个变量是“必须怎样”、“一定会是怎样”’则取一个值满足“必须要”的条件再取多个不满足的从多个角度去违背这个条件
            4. 如果一个变量是布尔类型，则取一个对一个错的
        - 在找到有效和无效等价类如何找测试数据
            1. 有效等价类：要尽可能多的覆盖有效等价类
            2. 无效等价类：每找到一组数据至少覆盖一组无效等价类

        - 如果功能模块的输入是多个，多个自变量放在一起如何找有效等价类、无效等价类、测试数据。以一个具有自变量X1、X2的函数F为例，X1取值范围为[a, b)、[b, c)、[c, d]；X2取值范围为[e, f)、[f, g]。仅考虑有标记的方块内为一般等价类测试（不处理无效数据的测试）、所有方块都考虑为健壮等价类测试（进行无效数据处理的测试）
            1. **弱一般等价类**：有假设前提。是单缺陷的，即假设系统出现的缺陷很少是由两个及以上的输入变量共同出现缺陷而引起的。选取的测试用例覆盖所有的有效等价类对于X1（横轴）：[a, b)、[b, c)、[c, d]都需要覆盖到；对于X2（纵轴）：[e, f)、[f, g]都需要覆盖到。保证了这两点的情况下，就可以任意取点了  
            2. **强一般等价类**：有假设前提。是单缺陷的，即假设系统出现的缺陷很少是由两个及以上的输入变量共同出现缺陷而引起的。考虑无效值，对有效输入，测试用例的设计等同于弱一般等价类；对无效输入，测试用例需要保证拥有一个无效值（比如某一变量的有效类的取值范围为x、y、z，则无效类为x-和z+，加起来取值范围一共：x-、x、y、z、z+），并保持其余的值都是有效的。
            3. **弱健壮等价类**：有假设前提。是单缺陷的，即假设系统出现的缺陷很少是由两个及以上的输入变量共同出现缺陷而引起的。考虑无效值，对有效输入，测试用例的设计等同于弱一般等价类；对无效输入，测试用例需要保证拥有一个无效值（比如某一变量的有效类的取值范围为x、y、z，则无效类为x-和z+，加起来取值范围一共：x-、x、y、z、z+），并保持其余的值都是有效的。
            4. **强健壮等价类**：基于多缺陷假设所有的取值范围取笛卡尔积（比如某一变量的有效类的取值范围为x、y、z，则无效类为x-和z+，加起来取值范围一共：x-、x、y、z、z+，再与另一变量的取值范围取笛卡尔积）
            5. ***在找测试数据时:*** 对于**单缺陷**的，即只有一个输入变量是处于无效等价类，其他所有输入变量都处在有效等价类中。包含：单缺陷有效值、单缺陷无效值。对于**多缺陷**的，即多个输入变量同时出现错误引起的。包含：有效值、无效值
        - **与边界值分析结合：** 先划分等价类，再结合边界值产生测试用例。边界值分析中也有假设前提：单缺陷。
            - 一般的边界值分析
              1. 有效范围：最小的，比最小大一点的，正常值，最大的，比最大小一点的
              2. 无效范围：比最小更小，比最大更大
              3. 共七个，再分单缺陷和多缺陷，这样设计测试用例就会指数上升
            - 常见的边界值
              1. 16bit整数32767～-32768
              2. 报表第一行和最后一行
              3. 屏幕光标最左上和最右下
              4. 数组的第一个和最后一个
              5. 循环的第0、1、倒数第一、倒数第二次  
    - **因果图：** 找出所有的原因，找出结果，可能还有中间结果产生。
      - 从输入考虑
        1. I：连虚线出去，如连到ab，表示ab中至少有一个必须成立
        2. E：连虚线出去，如连到ab，表示ab不能同时成立
        3. R：如处于a指向b的虚线三角箭头上，表示a出现时b也必须出现，不可能一个出现一个不出现 
      - 从输出考虑
        1. M：如处于a指向b的虚线三角箭头上，表示a为1时b必须为0，a为0时b值不定 
      - 连线：恒等
      - ～：非
      - ∨：或
      - ∧：且
      - ci：原因
      - ei：结果
      - 画出因果图后，根据图得到决策表从而得到相应的测试数据：原因节点+中间节点为条件桩，结果节点为动作桩
    - **判定表：** 适合于问题有多个条件，条件有多种组合执行不同操作（有很多if、else if、else），不能表达循环结构。最严格、最具有逻辑性。规则：条件的任意组合，判定表中的一列（贯穿条件项和动作项）。判定表有多少列就代表有多少条规则。规则的化简：有的规则相互包含，可以化简
    - **错误推测法**

- **白盒测试**：白盒测试与黑盒测试相反，需要了解软件中的结构。白盒测试也叫结构化测试，玻璃盒测试。
  - **逻辑覆盖**
    - 语句覆盖->判定覆盖->判定/条件覆盖->条件组合覆盖->路径覆盖
        \\_条件覆盖/12
    - 语句覆盖：每条语句执行一次
    - 判定覆盖：每个判定分支至少执行一次
    - 条件覆盖：每个判定条件应取到各种可能的值
    - 判定/条件覆盖：同时满足判定和条件
    - 条件组合覆盖：每个判定条件的每一种组合各出现一次
    - 路径覆盖：每一条可能的路径至少执行一次
  - **关系**
    - 条件组合覆盖＞判定覆盖＞语句覆盖(即如果达到条件组合覆盖，就达到判定覆盖和语句覆盖：如果达到判定覆盖，就达到语句覆盖，下面类似理解)。
    - 条件组合覆盖＞条件覆盖。
    - 条件覆盖不一定包含判定覆盖、语句覆盖。
    - 判定覆盖不一定包含条件覆盖。
    - 路径覆盖，判定覆盖＞语句覆盖。
  - **基本路径测试**
    - 基于程序圈复杂度产生的测试方法，画出控制流程图，算圈复杂度，找到独立路径并压缩为基本路径集合，根据集合中每条路径设计用例。把复合逻辑表达式拆成单个表达式。圈复杂度用于计算程序的基本的独立路径数目（每条新的独立路径都必须包含一条新的有向边，从入口到出口互不相同的路径数）
      - 圈复杂的V(G) = e - n + 2p【边-节点+2*连接区域数，连接区域p通常为1】=P+1【判定节点数+1】
      - 一般来说，一个单元模块的最大复杂度V(G)<10
    - 如果把覆盖的路径数压缩到一定限度内，例如程序中的循环体只执行0次和1次，就成为基本路径测试，通过导出基本路径集合，从而设计测试用例，保证这些路径至少通过一次
  - **基于数据流的测试**
    - 基于真的数据定义到数据的使用来进行测试，需要找到定义的节点（包括赋值的和比较的）和使用的节点
      - 定义节点DEF：输入语句、赋值语句、循环语句和过程调用；变量的值会发生变化的语句
      - 使用节点USE：输出语句、赋值语句、条件语句、循环控制语句、过程调用
    - 需要找到所有这段功能代码从哪里开始定义，到哪里开始执行，把路径找出来。什么是定义使用路径（某一变量在最初节点定义到最终节点被使用）、定义清除路径（某一个变量从它的定义节点到使用节点这个过程中没有对这个变量进行二次定义）
  - **循环测试**
    - 前提是程序是结构化的。简单循环测试
      - 0次通过循环
      - 1次通过循环
      - 2次通过循环
      - m次通过循环（m<=循环最大次数）
      - m-1，m，m+1次通过循环
- **黑盒测试与白盒测试的优缺点**
  - **黑盒测试**，优点：不需要了解软件实现细节，软件内部实现机制更改时，一般不必修改用例实现相对简单，以用户角度出发。缺点：无法保证软件代码内各主要路径都被覆盖到，容易导致测试不很完全
  - **白盒测试**，优点：针对软件代码和路径进行测试，相对易于调试，容易发现bug产生的原因。缺点：对测试人员的编程能力要求高，软件实现代码改变，测试用例一般也需要改变。

- 功能测试

- 兼容性测试

- 性能测试

- 安全测试

- 压力测试

测试的过程
===

单元测试
---
+ 单元测试的内容
  + 模块接口的测试
  - 局部数据结构的测试
  - 独立路径测试
  - 错误处理测试
  - 边界测试
- 单元测试的模块
  - 被测模块：被测试的程序的模块
  - 驱动模块：用来模拟测试模块的上一级模块，相当于被测模块的主程序
  - 桩模块：用来模拟被测模块工作过程中所调用的模块
- 单元测试的工具：Junit相关的概念：以插入断言的方式进行测试（类似黑盒测试）
  - 针对被测代码或者被测的功能点先创建测试类，然后在类里面创建一个个测试方法。通过实例化对象调用被测方法，用断言进行实际值预期值比较。
- 单元测试的方法
  - 以白盒测试法为主（覆盖），先静态检查代码是否符合规范，再动态运行代码，检查结果。除了需要验证结果是否正确，还需要检查程序的容错能力、边界值处理等问题。

集成测试
---
- 一次性的集成big-bang：把所有通过了单元测试的模块按设计要求一次全部组装起来，然后进行整体测试。时间虽变短了但急于求成。
- 渐进地集成
  1. 自上而下：从主程序模块开始按深度或广度优先策略边组装边测试
  2. 自下而上：从最底层模块开始组装和集成测试
  3. 汉堡包：两者进行结合，树状图每层画线，顶层采用自顶向下，底层采用自底向上
相邻的集成：上下三层进行集成
成对集成：先成对再相邻
基于MM路径的集成：MM路径不是可执行路径，描述单元之间的控制转移。

- 最终得到调用图，然后就会到基本路径测试，找复杂度，找路径，得到测试用例的套路

系统测试
---
黑盒为主

对哪些内容进行系统测试（9个）：易用性、国际化本地化、性能、功能、界面、兼容性、安全性、文档、安装

web系统测试
---
具体到如Web系统测试中的功能测试包含哪些内容、对cookies里面的内容进行测试属于Web系统测试里面的哪一项的测试（属于功能测试）
- 功能测试
  - 页面内容测试
  - 页面链接测试
  - 表单测试
  - Cookies测试、Session测试
  - 设计语言测试
  - 数据库测试
- 性能测试
  - 连接速度测试
  - 测试工具 LoadRunner
    1. 负载测试
    2. 压力测试
  - 网页性能Firefox插件：Yslow，Findbug，PageSpeed
  - Dynatrace检查网页性能
- 可靠性测试：不间断测试，看多久不出错
- 用户界面测试/易用性测试
  - 导航测试
  - 图形测试
  - 内容测试
  - 整体界面测试
- 安全性测试
- 兼容性测试
- 接口测试
  - 服务器接口
  - 外部接口
  - 错误处理

性能测试
---

性能测试是通过自动化的测试工具模拟多种正常、峰值以及异常负载条件来对系统的各项性能指标进行测试。

- 时间性能：软件的一个具体事务的响应时间
- 空间性能：软件运行时所消耗的系统资源
- 我让你背1袋米(轻松)
- 我让你背1袋米，但让你去操场上跑圈，看多久累倒（吃力）
- 我让你背3袋米去操场跑圈，看多久累倒（极限）
- 我让你背1袋、2袋、3袋、4袋…发现最多背3袋

负载测试让被测系统在其能忍受的压力的极限范围之内连续运行，来测试系统的可靠性。

- 系统能否处理某个时刻同时访问Web系统/某个页面的用户数量
- 超过了这个数量，会出现什么现象？
- 在线数据处理的数量


负载/压力测试关注什么？

验证系统能否同一时间响应大量的用户，用户传送大量数据时能否响应，系统能否长时间运行。

- 瞬间访问高峰
- 每个用户传送大量
- 数据长时间使用

LoadRunner性能测试工具原理：录制+回放模拟用户实际操作场景，监控并分析运行结果。

自动化测试
---
录制+回放+脚本 是主要的方式

常用的自动化测试的工具，哪些种类，每种有什么工具

- 功能测试工具：QTP
- 性能测试工具：LoadRunner
  1. 写脚本或者录制脚本
  2. 使用用户自定义参数
  3. 场景设计
  4. 产生虚拟用户的机制：使用控制器，来控制模拟多少用户。
  5. 使用监听器，查看测试结果