USE [master]
GO
/****** Object:  Database [Beer_Factory]    Script Date: 28.01.2015 13:28:53 ******/
CREATE DATABASE [Beer_Factory]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'Beer_Factory', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\Beer_Factory.mdf' , SIZE = 5120KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB )
 LOG ON 
( NAME = N'Beer_Factory_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL11.MSSQLSERVER\MSSQL\DATA\Beer_Factory_log.ldf' , SIZE = 1280KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)
GO
ALTER DATABASE [Beer_Factory] SET COMPATIBILITY_LEVEL = 110
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [Beer_Factory].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [Beer_Factory] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [Beer_Factory] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [Beer_Factory] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [Beer_Factory] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [Beer_Factory] SET ARITHABORT OFF 
GO
ALTER DATABASE [Beer_Factory] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [Beer_Factory] SET AUTO_CREATE_STATISTICS ON 
GO
ALTER DATABASE [Beer_Factory] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [Beer_Factory] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [Beer_Factory] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [Beer_Factory] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [Beer_Factory] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [Beer_Factory] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [Beer_Factory] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [Beer_Factory] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [Beer_Factory] SET  DISABLE_BROKER 
GO
ALTER DATABASE [Beer_Factory] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [Beer_Factory] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [Beer_Factory] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [Beer_Factory] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [Beer_Factory] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [Beer_Factory] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [Beer_Factory] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [Beer_Factory] SET RECOVERY FULL 
GO
ALTER DATABASE [Beer_Factory] SET  MULTI_USER 
GO
ALTER DATABASE [Beer_Factory] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [Beer_Factory] SET DB_CHAINING OFF 
GO
ALTER DATABASE [Beer_Factory] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [Beer_Factory] SET TARGET_RECOVERY_TIME = 0 SECONDS 
GO
USE [Beer_Factory]
GO
/****** Object:  Table [dbo].[Composition]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Composition](
	[id_composition] [int] IDENTITY(1,1) NOT NULL,
	[id_beer] [int] NULL,
	[id_raw] [int] NULL,
	[proportion] [float] NULL,
 CONSTRAINT [PK_Composition_1] PRIMARY KEY CLUSTERED 
(
	[id_composition] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Description]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Description](
	[id_beer] [int] IDENTITY(1,1) NOT NULL,
	[volume] [float] NULL,
	[alcohol] [float] NULL,
	[density] [float] NULL,
	[year] [int] NULL,
 CONSTRAINT [PK_Composition] PRIMARY KEY CLUSTERED 
(
	[id_beer] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Orders]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Orders](
	[id_order] [int] IDENTITY(1,1) NOT NULL,
	[id_user] [int] NULL,
	[data_in] [datetime] NULL,
	[total_cost] [float] NULL,
 CONSTRAINT [PK_Orders] PRIMARY KEY CLUSTERED 
(
	[id_order] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Production]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Production](
	[id_beer] [int] IDENTITY(1,1) NOT NULL,
	[name] [nchar](30) NOT NULL,
	[id_sort] [int] NULL,
	[number] [int] NULL,
	[price] [float] NULL,
 CONSTRAINT [PK_Production] PRIMARY KEY CLUSTERED 
(
	[id_beer] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Products_In_Order]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Products_In_Order](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[id_order] [int] NULL,
	[id_beer] [int] NULL,
	[number_to_buy] [int] NULL,
	[status] [bit] NULL,
	[data_out] [date] NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Raw_In_Order]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Raw_In_Order](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[id_order] [int] NULL,
	[id_raw] [int] NULL,
	[number_to_buy] [int] NULL,
	[data_out] [date] NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Raw_Materials]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Raw_Materials](
	[id_raw] [int] IDENTITY(1,1) NOT NULL,
	[name] [nchar](50) NOT NULL,
	[price] [money] NULL,
 CONSTRAINT [PK_Raw_1] PRIMARY KEY CLUSTERED 
(
	[id_raw] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Sort]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Sort](
	[id_sort] [int] IDENTITY(1,1) NOT NULL,
	[name] [nchar](20) NOT NULL,
	[grade] [nchar](5) NULL,
 CONSTRAINT [PK_Raw] PRIMARY KEY CLUSTERED 
(
	[id_sort] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[User_Type]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[User_Type](
	[id_type] [int] IDENTITY(1,1) NOT NULL,
	[type] [nchar](10) NULL,
 CONSTRAINT [PK_User_Type] PRIMARY KEY CLUSTERED 
(
	[id_type] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Users]    Script Date: 28.01.2015 13:28:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[id_user] [int] IDENTITY(1,1) NOT NULL,
	[fio] [nchar](50) NULL,
	[company] [nchar](50) NULL,
	[id_type] [int] NULL,
	[login] [nchar](20) NULL,
	[password] [nchar](20) NULL,
 CONSTRAINT [PK_Users_1] PRIMARY KEY CLUSTERED 
(
	[id_user] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]

GO
SET IDENTITY_INSERT [dbo].[Composition] ON 

INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (1, 1, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (2, 1, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (3, 1, 12, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (4, 1, 14, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (5, 2, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (6, 2, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (7, 2, 12, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (8, 2, 16, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (9, 3, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (10, 3, 2, 0.14)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (11, 3, 12, 0.06)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (12, 4, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (13, 4, 5, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (14, 4, 7, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (15, 4, 11, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (16, 5, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (17, 5, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (18, 5, 4, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (19, 5, 11, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (20, 6, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (21, 6, 2, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (22, 6, 3, 0.06)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (23, 6, 6, 0.01)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (24, 6, 12, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (25, 6, 15, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (26, 7, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (27, 7, 2, 0.14)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (28, 7, 11, 0.06)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (29, 8, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (30, 8, 2, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (31, 8, 4, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (32, 8, 8, 0.1)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (33, 8, 11, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (34, 9, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (35, 9, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (36, 9, 10, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (37, 9, 12, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (38, 10, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (39, 10, 2, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (40, 10, 10, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (41, 10, 12, 0.1)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (42, 10, 14, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (43, 11, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (44, 11, 2, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (45, 11, 10, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (46, 11, 12, 0.1)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (47, 11, 13, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (48, 12, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (49, 12, 2, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (50, 12, 10, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (51, 12, 12, 0.1)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (52, 12, 13, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (53, 13, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (54, 13, 2, 0.14)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (55, 13, 12, 0.06)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (56, 14, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (57, 14, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (58, 14, 12, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (59, 15, 1, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (60, 15, 2, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (61, 15, 9, 0.14)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (62, 15, 12, 0.06)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (63, 16, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (64, 16, 2, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (65, 16, 11, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (66, 16, 15, 0.1)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (67, 16, 17, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (68, 17, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (69, 17, 2, 0.01)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (70, 17, 10, 0.01)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (71, 17, 12, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (72, 17, 14, 0.02)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (73, 17, 15, 0.03)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (74, 17, 17, 0.04)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (75, 17, 18, 0.01)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (76, 18, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (77, 18, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (78, 18, 8, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (79, 18, 12, 0.08)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (80, 19, 1, 0.8)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (81, 19, 2, 0.07)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (82, 19, 10, 0.05)
INSERT [dbo].[Composition] ([id_composition], [id_beer], [id_raw], [proportion]) VALUES (83, 19, 12, 0.08)
SET IDENTITY_INSERT [dbo].[Composition] OFF
SET IDENTITY_INSERT [dbo].[Description] ON 

INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (1, 0.5, 0.5, 12, 1994)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (2, 0.5, 4.7, 11.5, 2004)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (3, 0.5, 4.8, 12, 1992)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (4, 0.5, 5.6, 15, 1994)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (5, 0.5, 5.3, 11.5, 2002)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (6, 0.5, 7, 17, 1994)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (7, 0.5, 5.4, 12, 1994)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (8, 0.5, 5, 12.5, 2001)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (9, 0.5, 8, 16, 1998)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (10, 0.5, 4.6, 11, 2010)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (11, 0.7, 5.4, 13, 2012)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (12, 0.7, 5.4, 13, 2012)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (13, 0.7, 5.3, 12, 2007)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (14, 0.7, 5.3, 12, 2007)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (15, 0.5, 4, 10, 2008)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (16, 0.5, 4.7, 11, 2006)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (17, 0.5, 4.7, 11, 2009)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (18, 0.5, 5, 12.5, 2013)
INSERT [dbo].[Description] ([id_beer], [volume], [alcohol], [density], [year]) VALUES (19, 0.5, 4.6, 13, 2013)
SET IDENTITY_INSERT [dbo].[Description] OFF
SET IDENTITY_INSERT [dbo].[Orders] ON 

INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (1, 8, CAST(0x0000961B00000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (2, 3, CAST(0x00009AE300000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (3, 6, CAST(0x00009C7E00000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (4, 9, CAST(0x00009CD500000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (5, 10, CAST(0x0000A06400000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (6, 5, CAST(0x0000A18100000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (7, 8, CAST(0x0000A17B00000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (8, 3, CAST(0x0000A29000000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (9, 5, CAST(0x0000A31D00000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (10, 7, CAST(0x0000A33200000000 AS DateTime), NULL)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (21, 5, CAST(0x0000A42A00000000 AS DateTime), 1452)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (22, 6, CAST(0x0000A42A00000000 AS DateTime), 502)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (23, 5, CAST(0x0000A42A00000000 AS DateTime), 288)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (24, 5, CAST(0x0000A42A00000000 AS DateTime), 16524)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (25, 3, CAST(0x0000A42A00000000 AS DateTime), 144)
INSERT [dbo].[Orders] ([id_order], [id_user], [data_in], [total_cost]) VALUES (26, 5, CAST(0x0000A42A00000000 AS DateTime), 312660)
SET IDENTITY_INSERT [dbo].[Orders] OFF
SET IDENTITY_INSERT [dbo].[Production] ON 

INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (1, N'Балтика 0 Безалкогольное      ', 1, 368, 53)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (2, N'Балтика 2 Светлое             ', 3, 345, 44)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (3, N'Балтика 3 Классическое        ', 3, 303, 46)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (4, N'Балтика 4 Оригинальное        ', 6, 366, 52)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (5, N'Балтика 5 Золотое             ', 5, 230, 69)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (6, N'Балтика 6 Портер              ', 6, 424, 60)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (7, N'Балтика 7 Экспортное          ', 1, 218, 51)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (8, N'Балтика 8 Пшеничное           ', 6, 342, 66)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (9, N'Балтика 9 Крепкое             ', 3, 264, 68)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (10, N'Балтика 20 Юбилейное          ', 5, 423, 58)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (11, N'Батлика Венское               ', 2, 454, 64)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (12, N'Балтика Калифорнийское        ', 2, 262, 41)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (13, N'Балтика Непастеризованное     ', 4, 131, 43)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (14, N'Балтика Нефильтрованное       ', 4, 263, 36)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (15, N'Балтика Lite                  ', 5, 214, 32)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (16, N'Балтика Кулер                 ', 5, 321, 42)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (17, N'Балтика Кулер Лайм            ', 5, 481, 49)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (18, N'Балтика München               ', 1, 580, 65)
INSERT [dbo].[Production] ([id_beer], [name], [id_sort], [number], [price]) VALUES (19, N'Балтика Praha                 ', 1, 497, 66)
SET IDENTITY_INSERT [dbo].[Production] OFF
SET IDENTITY_INSERT [dbo].[Products_In_Order] ON 

INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (1, 1, 16, 46, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (2, 1, 1, 11, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (3, 3, 10, 43, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (4, 3, 13, 21, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (5, 4, 17, 37, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (6, 5, 6, 14, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (7, 6, 3, 15, 1, CAST(0x85390B00 AS Date))
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (8, 6, 8, 13, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (9, 6, 2, 40, 1, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (10, 7, 19, 21, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (11, 8, 8, 36, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (12, 9, 15, 19, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (13, 10, 19, 28, 1, CAST(0x85390B00 AS Date))
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (27, 22, 1, 4, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (28, 22, 10, 5, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (29, 23, 3, 2, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (30, 23, 17, 4, 0, NULL)
INSERT [dbo].[Products_In_Order] ([id], [id_order], [id_beer], [number_to_buy], [status], [data_out]) VALUES (31, 24, 7, 324, 0, NULL)
SET IDENTITY_INSERT [dbo].[Products_In_Order] OFF
SET IDENTITY_INSERT [dbo].[Raw_In_Order] ON 

INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (1, 2, 7, 5, CAST(0x79390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (2, 2, 9, 12, CAST(0x79390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (3, 2, 16, 1, CAST(0x79390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (4, 2, 8, 14, CAST(0x79390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (5, 8, 11, 8, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (6, 8, 12, 6, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (7, 8, 7, 11, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (8, 8, 1, 4, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (9, 8, 3, 5, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (10, 8, 6, 9, CAST(0x81390B00 AS Date))
INSERT [dbo].[Raw_In_Order] ([id], [id_order], [id_raw], [number_to_buy], [data_out]) VALUES (13, 25, 3, 12, CAST(0x85390B00 AS Date))
SET IDENTITY_INSERT [dbo].[Raw_In_Order] OFF
SET IDENTITY_INSERT [dbo].[Raw_Materials] ON 

INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (1, N'очищенная питьевая вода                           ', 7.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (2, N'светлый ячменный солод                            ', 2.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (3, N'жженный ячменный солод                            ', 2.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (4, N'карамельный ячменный солод                        ', 2.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (5, N'светлый карамельный солод                         ', 7.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (6, N'темный карамельный солод                          ', 6.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (7, N'ржаной солод                                      ', 4.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (8, N'пшеничный солод                                   ', 7.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (9, N'зеленый солод                                     ', 10.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (10, N'пивоваренный ячмень                               ', 9.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (11, N'хмель                                             ', 3.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (12, N'хмелепродукты                                     ', 9.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (13, N'солодовый экстракт                                ', 5.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (14, N'мальтозная патока                                 ', 4.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (15, N'дрожжи                                            ', 4.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (16, N'рис                                               ', 2.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (17, N'кукурузная крупа                                  ', 6.0000)
INSERT [dbo].[Raw_Materials] ([id_raw], [name], [price]) VALUES (18, N'лимонный сок                                      ', 4.0000)
SET IDENTITY_INSERT [dbo].[Raw_Materials] OFF
SET IDENTITY_INSERT [dbo].[Sort] ON 

INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (1, N'Экспортное          ', N'lager')
INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (2, N'Коллекция пивовара  ', N'lager')
INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (3, N'Традиционное        ', N'lager')
INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (4, N'Разливное           ', N'lager')
INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (5, N'Особое              ', N'lager')
INSERT [dbo].[Sort] ([id_sort], [name], [grade]) VALUES (6, N'Избранное           ', N'dark ')
SET IDENTITY_INSERT [dbo].[Sort] OFF
SET IDENTITY_INSERT [dbo].[User_Type] ON 

INSERT [dbo].[User_Type] ([id_type], [type]) VALUES (1, N'manager   ')
INSERT [dbo].[User_Type] ([id_type], [type]) VALUES (2, N'stockman  ')
INSERT [dbo].[User_Type] ([id_type], [type]) VALUES (3, N'client    ')
SET IDENTITY_INSERT [dbo].[User_Type] OFF
SET IDENTITY_INSERT [dbo].[Users] ON 

INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (1, N'Кулагин Валентин Игоревич                         ', N'ООО "Балтика"                                     ', 1, N'manager_1           ', N'manager_1           ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (2, N'Ершова Любовь Ярославовна                         ', N'ООО "Балтика"                                     ', 1, N'manager_2           ', N'manager_2           ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (3, N'Лапин Василий Данилович                           ', N'ООО "Балтика"                                     ', 2, N'stockman_1          ', N'stockman_1          ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (4, N'Новикова елена Викторовна                         ', N'ООО "Балтика"                                     ', 2, N'stockman_2          ', N'stockman_2          ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (5, N'Кузнецов Михаил Александрович                     ', N'ООО "О''кей"                                       ', 3, N'1                   ', N'1                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (6, N'Иванова Марина Юрьевна                            ', N'ООО "Пятерочка"                                   ', 3, N'2                   ', N'2                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (7, N'Тетерин Даниил Романович                          ', N'ООО "Лента"                                       ', 3, N'3                   ', N'3                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (8, N'Самойлова Светлана Матвеевна                      ', N'ООО "Spar"                                        ', 3, N'4                   ', N'4                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (9, N'Матвеев Егор Дмитриевич                           ', N'ООО "Магнит"                                      ', 3, N'5                   ', N'5                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (10, N'Воронова Анна Викторовна                          ', N'ИП "Продукты у Анны"                              ', 3, N'6                   ', N'6                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (11, N'Баранов Борис Филиппович                          ', N'ИП "Боря"                                         ', 3, N'7                   ', N'7                   ')
INSERT [dbo].[Users] ([id_user], [fio], [company], [id_type], [login], [password]) VALUES (12, N'Шарова Алиса Борисовна                            ', N'ИП "Алиса"                                        ', 3, N'8                   ', N'8                   ')
SET IDENTITY_INSERT [dbo].[Users] OFF
ALTER TABLE [dbo].[Sort] ADD  CONSTRAINT [DF_Raw_Materials_lager_or_dark]  DEFAULT (N'lager') FOR [grade]
GO
ALTER TABLE [dbo].[Composition]  WITH CHECK ADD  CONSTRAINT [FK_Composition_Production] FOREIGN KEY([id_beer])
REFERENCES [dbo].[Production] ([id_beer])
GO
ALTER TABLE [dbo].[Composition] CHECK CONSTRAINT [FK_Composition_Production]
GO
ALTER TABLE [dbo].[Composition]  WITH CHECK ADD  CONSTRAINT [FK_Composition_Raw_Materials] FOREIGN KEY([id_raw])
REFERENCES [dbo].[Raw_Materials] ([id_raw])
GO
ALTER TABLE [dbo].[Composition] CHECK CONSTRAINT [FK_Composition_Raw_Materials]
GO
ALTER TABLE [dbo].[Orders]  WITH CHECK ADD  CONSTRAINT [FK_Orders_Users] FOREIGN KEY([id_user])
REFERENCES [dbo].[Users] ([id_user])
GO
ALTER TABLE [dbo].[Orders] CHECK CONSTRAINT [FK_Orders_Users]
GO
ALTER TABLE [dbo].[Production]  WITH CHECK ADD  CONSTRAINT [FK_Production_Description] FOREIGN KEY([id_beer])
REFERENCES [dbo].[Description] ([id_beer])
GO
ALTER TABLE [dbo].[Production] CHECK CONSTRAINT [FK_Production_Description]
GO
ALTER TABLE [dbo].[Production]  WITH CHECK ADD  CONSTRAINT [FK_Production_Sort] FOREIGN KEY([id_sort])
REFERENCES [dbo].[Sort] ([id_sort])
GO
ALTER TABLE [dbo].[Production] CHECK CONSTRAINT [FK_Production_Sort]
GO
ALTER TABLE [dbo].[Products_In_Order]  WITH CHECK ADD  CONSTRAINT [FK_Products_In_Order_Orders] FOREIGN KEY([id_order])
REFERENCES [dbo].[Orders] ([id_order])
GO
ALTER TABLE [dbo].[Products_In_Order] CHECK CONSTRAINT [FK_Products_In_Order_Orders]
GO
ALTER TABLE [dbo].[Products_In_Order]  WITH CHECK ADD  CONSTRAINT [FK_Products_In_Order_Production] FOREIGN KEY([id_beer])
REFERENCES [dbo].[Production] ([id_beer])
GO
ALTER TABLE [dbo].[Products_In_Order] CHECK CONSTRAINT [FK_Products_In_Order_Production]
GO
ALTER TABLE [dbo].[Raw_In_Order]  WITH CHECK ADD  CONSTRAINT [FK_Raw_In_Order_Orders] FOREIGN KEY([id_order])
REFERENCES [dbo].[Orders] ([id_order])
GO
ALTER TABLE [dbo].[Raw_In_Order] CHECK CONSTRAINT [FK_Raw_In_Order_Orders]
GO
ALTER TABLE [dbo].[Raw_In_Order]  WITH CHECK ADD  CONSTRAINT [FK_Raw_In_Order_Raw_Materials] FOREIGN KEY([id_raw])
REFERENCES [dbo].[Raw_Materials] ([id_raw])
GO
ALTER TABLE [dbo].[Raw_In_Order] CHECK CONSTRAINT [FK_Raw_In_Order_Raw_Materials]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_Users_User_Type] FOREIGN KEY([id_type])
REFERENCES [dbo].[User_Type] ([id_type])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_Users_User_Type]
GO
USE [master]
GO
ALTER DATABASE [Beer_Factory] SET  READ_WRITE 
GO
