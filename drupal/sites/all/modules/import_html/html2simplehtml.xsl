<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xhtml="http://www.w3.org/1999/xhtml"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:exsl="http://exslt.org/common"
> 
<!--  xmlns="http://www.w3.org/1999/xhtml" causes bogus namespaces on imported elements -->

	<xsl:output method="xml" encoding="UTF-8" />
	<!-- 
		Analyse a generic web page and return a vanilla-as-possible
		pure XHTML version.

		Although this is supposed to be 'simple' it will 
		also support multiple documents in one file, if the input
		has them in a 'exsl:document' wrapper.
		

		To find the nodes by local name without namespaces handicapping me,
		Input html must either have no namespace ( select="html" )
		or be in the xhtml namespace ( select="xhtml:html" ).
		Use these two patterns at all times when matching nodes by name :-(

		Another work-around is ( select="*[local-name()='html']" )

		... This may be avoided slightly by adjusting the input namespace 
		during pre-processing ... although the syntax will still require 
		the prefix - a doc with any namespace requires the prefix to
		be used from then on.

		The xsl:text nodes are just scattered around to force some pretty-printing on the output
		
		Note the use of xml:id for items we intend to find later.
		This IS significant and important for performance.

		.dan.
	-->

	<!-- 
		Caller can define the id of the 'content' block to be extracted 
	-->
	<xsl:param name='contentid'>content</xsl:param>

	<!--
		If $xmlid is set, this document will insert xml:id along with normal html:id
		THESE ARE DIFFERENT THINGS. 
		xml:id is much better for the DOM,
		html:id is just another attribute.
		http://php5.bitflux.org/xmlonspeed/slide_20.php
		Normally these are good, but need to be turned off if doing multiple 
		documents as duplicate ids are errors.
	-->
	<xsl:param name="xmlid"></xsl:param>
	
	<xsl:template match="/*[descendant::exsl:document]">
		<!-- 
			This document contains sub documents. Process them individually.
		-->	
		<exsl:documents>
		<xsl:for-each select = "descendant::exsl:document">
			<xsl:text>
			</xsl:text>
				<exsl:document>
				<xsl:copy-of select="@*" />
				<xsl:call-template name="html_doc"/>
				</exsl:document>
			<xsl:text>
			
			</xsl:text>
		</xsl:for-each>
		</exsl:documents>
	</xsl:template>


	<xsl:template name="html_doc" match="/*[not(descendant::exsl:document)]">	
	<!-- 
	Main page layout.
	Current context node is either exsl:document or the html tag.
	Either way, head and body are the immediate children.
	-->
		<html>
		<head>
		<!-- META And Header extraction -->
		
	    <title>
			<xsl:call-template name="get-title" />
	    </title>

		<xsl:text>
		</xsl:text>

		<meta name="description" id="teaser" >
			<xsl:if test="$xmlid"><xsl:attribute name="xml:id">teaser</xsl:attribute></xsl:if>
			<xsl:attribute name="value">
				<xsl:call-template name="get-description" />
			</xsl:attribute>
		</meta>
		
		<xsl:if test="@href">
			<!-- copy the container exsl:document@href into our meta information -->
			<meta name="path" id="path" >
				<xsl:if test="$xmlid"><xsl:attribute name="xml:id">teaser</xsl:attribute></xsl:if>
				<xsl:value-of select="@href" />
			</meta>
		</xsl:if>


		<xsl:for-each select=".//head|.//xhtml:head">
			<xsl:for-each select="meta[@name]|xhtml:meta[@name]|rel|xhtml:rel|style|xhtml:style">
				<!-- copy most of the head - but NOT metas with http-equiv -->
				<xsl:copy><xsl:for-each select="@*"><xsl:copy></xsl:copy></xsl:for-each></xsl:copy>
			</xsl:for-each>
		<xsl:text>
		</xsl:text>
		</xsl:for-each>
		
		</head>
		<xsl:text>
		
		</xsl:text>
		<body>
			<h1 id="pagetitle">
				<xsl:if test="$xmlid"><xsl:attribute name="xml:id">pagetitle</xsl:attribute></xsl:if>
				<xsl:call-template name="get-title" />
			</h1>
			<div id="content">
				<xsl:if test="$xmlid"><xsl:attribute name="xml:id">content</xsl:attribute></xsl:if>
				<xsl:call-template name="get-content" >
					<xsl:with-param name="contentid" select="$contentid" />
				</xsl:call-template >
			</div>
		</body>

		</html>
	</xsl:template>




	<xsl:template name="get-title">
		<!-- 
			Note: TODO 
			Need to deal with the possible difference between 
			document title and H1 display title .
			Look for H1 or anything id=pagetitle first
			If that fails, use the meta title.
			Some exceptions to do so are defined later.
			
			HOW to remove the header from the body once i've found it?
		-->
			<xsl:choose>
	
				<xsl:when test="descendant::*[local-name()='h1']">
			    	<xsl:value-of select="normalize-space(descendant::*[local-name()='h1'])" />
				</xsl:when>
				
				<xsl:when test="//*[@id='pagetitle']">
					<!-- 
						Nice sites set the id of their title.
						May add other #ids here as I find them
					-->
			    	<xsl:value-of select="normalize-space(descendant::*[@id='pagetitle'])" />
				</xsl:when>

				<xsl:when test="count(descendant::h2|descendant::xhtml:h2)=1">
					<!-- 
						Maybe it used an h2 because h1 was ugly.
						If there is ONLY ONE h2, use that
					-->
			    	<xsl:value-of select="normalize-space(descendant::h2|descendant::xhtml:h2)" />
				</xsl:when>
				
				<xsl:otherwise>
					<!-- 
						In practice, the html head title is often more verbose than we want
						and too often it's the same across whole sections, but it'll have to do.
					-->
			    	<xsl:value-of select="normalize-space(descendant::*[name() = 'title'])" />
				</xsl:otherwise>
				<!--
				  Any of these steps may fail if the heading contains only html, eg
				  <h1><img src='header.gif' /></h1>
				-->
			</xsl:choose>
	</xsl:template>
	
	<xsl:template match="*[local-name()='h1']|*[@id='pagetitle']">
	<!-- remove these from the flow altogether -->
	</xsl:template>


	<xsl:template name="get-content">
			<!--	
				Attempt to find any defined content divs. 
				A set of names is scanned for, and if any elements are 
				found with those ids or classes, that is used as the content.
				We go one-by-one through {user-defined contentid} followed
				by 'content', 'bodyCopy' and 'main'.
				If more than one match is found at the same level of precedence,
				the results are concatenated.
				
				Failing that, include everything found in the body.
			-->

			<xsl:param name="contentid"/>

		
			<xsl:choose>
				<!--
					Need to detect them before using them to avoid 
					duplication of content if more than one match is valid.
					So do a look-see test before select.
					Cannot group these tests, because we need to ensure 
					these checks happen in order of desired precedence.
					
					When we've found our content, we discard its type and return its naked contents.
				-->

				<xsl:when test="descendant::*[@id=$contentid or @class=$contentid ]">
					<!-- user-defined id tag -->
					<xsl:comment>Imported From the element called <xsl:value-of select="$contentid"/></xsl:comment>
					<xsl:for-each select="descendant::*[@id=$contentid or @class=$contentid]" >
						<xsl:apply-templates />
						<xsl:text>
						</xsl:text>
					</xsl:for-each>
				</xsl:when>

				<xsl:when test="descendant::*[@id='main' or @class='main']">
					<xsl:comment>Imported From the element called main</xsl:comment>
					<xsl:for-each select="descendant::*[@id='main' or @class='main']" >
						<xsl:apply-templates />
						<xsl:text>
						</xsl:text>
					</xsl:for-each>
				</xsl:when>

				<xsl:when test="descendant::*[@id='content' or @class='content']">
					<xsl:comment>Imported From the element called content</xsl:comment>
					<xsl:for-each select="descendant::*[@id='content' or @class='content']" >
						<xsl:apply-templates />
						<xsl:text>
						</xsl:text>
					</xsl:for-each>
				</xsl:when>

				<xsl:when test="descendant::*[@id='bodyCopy' or @class='bodyCopy']">
					<xsl:comment>Imported From the element called bodyCopy</xsl:comment>

					<xsl:for-each select="descendant::*[@id='bodyCopy' or @class='bodyCopy']" >
						<xsl:apply-templates />
					</xsl:for-each>

				</xsl:when>

			  
				<xsl:when test="descendant::*[@class='reference']">
				<!--
					This one grabs content from php.net documentation
				-->
					<xsl:comment>Imported From the element called reference</xsl:comment>
					<xsl:for-each select="descendant::*[@class='reference']" >
						<xsl:apply-templates />
					</xsl:for-each>
				</xsl:when>

				<xsl:otherwise>
					<xsl:text>
									
					</xsl:text>
					<xsl:comment>Couldn't selectively extract content, Imported Full Body :(</xsl:comment>
					<xsl:text>
					
					</xsl:text>
					<!-- Absolutely no magic here - dump it ALL in -->
					<xsl:apply-templates select="descendant::body/*|descendant::xhtml:body/*|descendant::body/text()|descendant::xhtml:body/text()"/>
					

				</xsl:otherwise>

			</xsl:choose>
	</xsl:template>
	
	<xsl:template name="get-description">
		<!-- 
			Look for 
			a defined meta tag, 
			a 'description' id, 
			a 'description' class, 
			or the first paragraph. 
			In that order.
			Description text is a flat string with no formatting!
		-->
		<xsl:choose>
			<xsl:when test="descendant::meta[@name='description']">
		    	<xsl:value-of select="descendant::meta[@name='description']" />
			</xsl:when>
			<xsl:when test="descendant::*[@id='description']">
		    	<xsl:value-of select="descendant::*[@id='description']" />
			</xsl:when>
			<xsl:when test="descendant::*[@class='description']">
		    	<xsl:value-of select="descendant::*[@class='description']" />
			</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="set" select="descendant::p|descendant::xhtml:p"/>
				<xsl:for-each select="$set[1]">
					<xsl:value-of select="descendant::*[@class='description']" />
				</xsl:for-each>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>


	<!-- Identity transformation template - to inline existing HTML  -->			
	<xsl:template name="passthrough" match="@*|node()|text()">
	  <xsl:copy>
		<xsl:apply-templates select="@*|node()|text()"/>
	  </xsl:copy>
	</xsl:template>

</xsl:stylesheet>