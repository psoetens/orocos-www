<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xhtml="http://www.w3.org/1999/xhtml"
>
	<xsl:output method = "xml" encoding="UTF-8" />
	<!-- 
	Read input from ModernDrunkard Magazine
	.dan.
	-->
	
	<xsl:template match="/">	
		<nodes>
		<xsl:apply-templates select="html|xhtml:html" />
		</nodes>
	</xsl:template>

	<xsl:template match="html|xhtml:html">	
		<node type="story">
		
	    <title>
			<xsl:choose>
				
				<xsl:when test="//*[@class='drunkhdr']">
			    	<xsl:value-of select="//*[@class='drunkhdr']" />
				</xsl:when>

				<xsl:otherwise>
					<!-- 
						In practice, the html title is often more verbose than we want
						and too often it's the same across whole sections, but it'll have to do.
					-->
				
			    	<xsl:value-of select="head/title|xhtml:head/xhtml:title" />
				</xsl:otherwise>
			</xsl:choose>
	    </title>

<xsl:text>
</xsl:text>


		<!-- Content extraction -->
		<teaser>
		<!-- Grab the first two paragraphs ... found anywhere in the doc -->

			<xsl:variable name="set" select="//p|//xhtml:p"/>
			<!-- <xsl:for-each select="$set[1]|$set[2]"> OK, just one para -->
			<xsl:for-each select="$set[1]">
				<xsl:call-template name="escapeall" />
 			</xsl:for-each>

		</teaser>

<xsl:text>

</xsl:text>
		
		<body>
			<!--	Attempt to find any defined content divs. Failing that, include everything	-->
			<xsl:choose>
				<!--
					Need to detect them before using them to avoid 
					duplication of content if more than one match is valid.
					So look-see before select
				-->

				<xsl:when test="//*[@height='0' and @bordercolor='#000000' and @bgcolor='#FFFFFF' ]">
					<xsl:for-each select="//*[@height='0' and @bordercolor='#000000' and @bgcolor='#FFFFFF' ]/*" >
						<xsl:call-template name="escapeall" />
					</xsl:for-each>
				</xsl:when>

				<xsl:otherwise>

					<xsl:text>

					</xsl:text>
					<xsl:comment>Imported Full Body :(</xsl:comment>
					<xsl:text>

					</xsl:text>
				<!-- Absolutely no magic here - dump it ALL in -->

					<xsl:for-each select="//body/*|//xhtml:body/*" >
						<xsl:call-template name="escapeall" />
					</xsl:for-each>
					

				</xsl:otherwise>
			</xsl:choose>
		</body>

		<xsl:text>
		</xsl:text>
		
		<user uid="1">dman</user>

<xsl:text>
</xsl:text>
			
    	</node>

<xsl:text>

</xsl:text>

	</xsl:template>


	<!-- Identity transformation template - to inline existing HTML  -->			
	<xsl:template name="passthrough" match="@*|node()|text()">
	  <xsl:copy>
		<xsl:apply-templates select="@*|node()|text()"/>
	  </xsl:copy>
	</xsl:template>



	<!-- 
		Flatten all HTML or XML into escaped code - safe text for embedding without parsing
		I thought I could find a code snippet to do this at Mulberry or Pawsons FAQ, but no.
		May miss out on advanced nodes (comments)
		.dan. Sep 2005
	-->			
	<xsl:template name="escapeall">

	<xsl:choose>
		<!-- first, a couple of exceptions that are NOT to be rendered -->
		<xsl:when test="name()='h1'"><!-- skip --></xsl:when>
		<xsl:when test="@id='pagetitle'"><!-- skip --></xsl:when>

		<xsl:when test="name()">
			<!-- named nodes get the full works -->

			<xsl:text>&lt;</xsl:text>
			<xsl:value-of select="name()" />
			<xsl:text> </xsl:text>
			<xsl:for-each select="@*" >
				<xsl:value-of select="name()" />
				<xsl:text>="</xsl:text>
				<xsl:value-of select="." />
				<xsl:text>" </xsl:text>
			</xsl:for-each>
			
			<xsl:choose>
			<xsl:when test="node()|*">
				<!-- has content... recurse -->

				<xsl:text>&gt;</xsl:text>
				<xsl:for-each select=" * | comment() | processing-instruction() | text()">
					<xsl:call-template name="escapeall" />
				</xsl:for-each>
		
				<xsl:text>&lt;/</xsl:text>
				<xsl:value-of select="name()" />
				<xsl:text>&gt;</xsl:text>

			</xsl:when>
			<xsl:otherwise>
				<xsl:text>/&gt;</xsl:text>
			</xsl:otherwise>
			</xsl:choose>
	
		</xsl:when>
		<xsl:otherwise> 
			<!-- a node with no name ... must be text -->
			<xsl:copy-of select="."/>
		</xsl:otherwise>
		</xsl:choose>


	</xsl:template>


</xsl:stylesheet>